#include "TutorialGame.h"
#include "../CSC8503Common/GameWorld.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Common/TextureLoader.h"
#include "../CSC8503Common/PositionConstraint.h"
#include "../../CSC8599Common/Player.h"
#include "../../CSC8599Common/Monster.h"
#include "../../CSC8599Common/Pet.h"
#include "../../CSC8599Common/State.h"
#include "../../CSC8599Common/StateTransition.h"
#include "../../CSC8599Common/PlalyerAIController.h"
#include  "../../CSC8599Common/PlayerController.h"
#include "../../CSC8599Common/Dragon.h"
#include "../CSC8503Common/StateMachine.h"
#include "ltlf.h"
#include "StateMachineParser.h"

using namespace NCL;
using namespace CSC8503;
using namespace CSC8599;

TutorialGame::TutorialGame() {
	world = new GameWorld();
	renderer = new GameTechRenderer(*world);
	physics = new PhysicsSystem(*world);

	forceMagnitude = 10.0f;
	useGravity = false;
	inSelectionMode = false;

	Debug::SetRenderer(renderer);

	initStateMachine();
	InitialiseAssets();
	initEventHandler();

	auto envC = new Environment();
	envC->first = "DebugC";
	envC->second.emplace_back(_monster->get_monster_state_machine());
	envC->second.emplace_back(dynamic_cast<CSC8599::StateMachine*>(debug_state_machine->GetComponent("DebugC")));
	AdaptiveDebugSystem::getInstance()->insert(envC);

	auto envA = new Environment();
	envA->first = "DebugA";
	envA->second.emplace_back(dynamic_cast<CSC8599::StateMachine*>(debug_state_machine->GetComponent("DebugA")));
	AdaptiveDebugSystem::getInstance()->insert(envA);

	auto envB = new Environment();
	envB->first = "DebugB";
	envB->second.emplace_back(localPlayer->get_state_machine());
	envB->second.emplace_back(_pet->get_state_machine());
	envB->second.emplace_back(dynamic_cast<CSC8599::StateMachine*>(debug_state_machine->GetComponent("DebugB")));
	AdaptiveDebugSystem::getInstance()->insert(envB);
}

/*

Each of the little demo scenarios used in the game uses the same 2 meshes,
and the same texture and shader. There's no need to ever load in anything else
for this module, even in the coursework, but you can add it if you like!

*/
void TutorialGame::InitialiseAssets() {
	auto loadFunc = [](const string& name, OGLMesh** into) {
		*into = new OGLMesh(name);
		(*into)->SetPrimitiveType(GeometryPrimitive::Triangles);
		(*into)->UploadToGPU();
	};

	loadFunc("cube.msh", &cubeMesh);
	loadFunc("sphere.msh", &sphereMesh);
	loadFunc("Male1.msh", &charMeshA);
	loadFunc("courier.msh", &charMeshB);
	loadFunc("security.msh", &enemyMesh);
	loadFunc("coin.msh", &bonusMesh);
	loadFunc("capsule.msh", &capsuleMesh);

	loadFunc("Dragon.msh", &redDragonMesh);
	loadFunc("RobotKyle.msh", &PlayerMesh);
	loadFunc("DogPBR.msh", &MonsterMesh);
	loadFunc("TurtleShell.msh", &PetMesh);

	basicTex = (OGLTexture*)TextureLoader::LoadAPITexture("nyan.png");
	basicShader = new OGLShader("GameTechVert.glsl", "GameTechFrag.glsl");

	redDragonTex= (OGLTexture*)TextureLoader::LoadAPITexture("AlbedoDragon.png");
	PetTex = (OGLTexture*)TextureLoader::LoadAPITexture("AlbedoPet.png");
	MonsterTex = (OGLTexture*)TextureLoader::LoadAPITexture("AlbedoDog.png");
	PlayerTex = (OGLTexture*)TextureLoader::LoadAPITexture("Robot_Color.png");
	//InitCamera();
	InitWorld();
}

TutorialGame::~TutorialGame() {
	delete cubeMesh;
	delete sphereMesh;
	delete charMeshA;
	delete charMeshB;
	delete enemyMesh;
	delete bonusMesh;

	delete redDragonMesh;

	delete basicTex;
	delete basicShader;

	delete physics;
	delete renderer;
	delete world;
}

void TutorialGame::UpdateGame(float dt) {
	game_state_machine->Update(dt);

	EventSystem::getInstance()->Update(dt);

	AdaptiveDebugSystem::getInstance()->update(dt);

	renderer->Update(dt);

	Debug::FlushRenderables(dt);
	renderer->Render();
}

void TutorialGame::UpdateKeys() {
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::F1)) {
		EventSystem::getInstance()->Reset();
		InitWorld(); //We can reset the simulation at any time with F1
		selectionObject = nullptr;
		lockedObject = nullptr;
		initEventHandler();
	}

	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::F2)) {
		InitCamera(); //F2 will reset the camera to a specific default place
	}

	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::G)) {
		useGravity = !useGravity; //Toggle gravity!
		physics->UseGravity(useGravity);
	}
	//Running certain physics updates in a consistent order might cause some
	//bias in the calculations - the same objects might keep 'winning' the constraint
	//allowing the other one to stretch too much etc. Shuffling the order so that it
	//is random every frame can help reduce such bias.
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::F9)) {
		world->ShuffleConstraints(true);
	}
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::F10)) {
		world->ShuffleConstraints(false);
	}

	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::F7)) {
		world->ShuffleObjects(true);
	}
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::F8)) {
		world->ShuffleObjects(false);
	}

	if (lockedObject) {
		LockedObjectMovement();
	}
	else {
		DebugObjectMovement();
	}
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::F3)) {
		std::cout<<EventSystem::getInstance()->Print(0)<<std::endl;
	}

	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::F4)) {
		useDebugSM = !useDebugSM; //Toggle debug state machine!
	}
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::F5)) {
		std::cout << *AdaptiveDebugSystem::getInstance() << std::endl;
	}
}

void TutorialGame::LockedObjectMovement() {
	Matrix4 view = world->GetMainCamera()->BuildViewMatrix();
	Matrix4 camWorld = view.Inverse();

	Vector3 rightAxis = Vector3(camWorld.GetColumn(0)); //view is inverse of model!

	//forward is more tricky -  camera forward is 'into' the screen...
	//so we can take a guess, and use the cross of straight up, and
	//the right axis, to hopefully get a vector that's good enough!

	Vector3 fwdAxis = Vector3::Cross(Vector3(0, 1, 0), rightAxis);
	fwdAxis.y = 0.0f;
	fwdAxis.Normalise();

	Vector3 charForward = lockedObject->GetTransform().GetOrientation() * Vector3(0, 0, 1);
	Vector3 charForward2 = lockedObject->GetTransform().GetOrientation() * Vector3(0, 0, 1);

	float force = 100.0f;

	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::LEFT)) {
		lockedObject->GetPhysicsObject()->AddForce(-rightAxis * force);
	}

	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::RIGHT)) {
		Vector3 worldPos = selectionObject->GetTransform().GetPosition();
		lockedObject->GetPhysicsObject()->AddForce(rightAxis * force);
	}

	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::UP)) {
		lockedObject->GetPhysicsObject()->AddForce(fwdAxis * force);
	}

	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::DOWN)) {
		lockedObject->GetPhysicsObject()->AddForce(-fwdAxis * force);
	}

	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::NEXT)) {
		lockedObject->GetPhysicsObject()->AddForce(Vector3(0, -10, 0));
	}
}

void TutorialGame::DebugObjectMovement() {
	//If we've selected an object, we can manipulate it with some key presses
	if (inSelectionMode && selectionObject) {
		//Twist the selected object!
		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::LEFT)) {
			selectionObject->GetPhysicsObject()->AddTorque(Vector3(-10, 0, 0));
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::RIGHT)) {
			selectionObject->GetPhysicsObject()->AddTorque(Vector3(10, 0, 0));
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::NUM7)) {
			selectionObject->GetPhysicsObject()->AddTorque(Vector3(0, 10, 0));
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::NUM8)) {
			selectionObject->GetPhysicsObject()->AddTorque(Vector3(0, -10, 0));
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::RIGHT)) {
			selectionObject->GetPhysicsObject()->AddTorque(Vector3(10, 0, 0));
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::UP)) {
			selectionObject->GetPhysicsObject()->AddForce(Vector3(0, 0, -10));
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::DOWN)) {
			selectionObject->GetPhysicsObject()->AddForce(Vector3(0, 0, 10));
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::NUM5)) {
			selectionObject->GetPhysicsObject()->AddForce(Vector3(0, -10, 0));
		}
	}
}

void TutorialGame::InitCamera() {
	world->GetMainCamera()->SetNearPlane(0.1f);
	world->GetMainCamera()->SetFarPlane(500.0f);
	world->GetMainCamera()->SetPitch(-15.0f);
	world->GetMainCamera()->SetYaw(330.0f);
	world->GetMainCamera()->SetPosition(Vector3(-60, 40, 120));
	lockedObject = nullptr;
}

void NCL::CSC8503::TutorialGame::MoveCameraToMenu()
{
	world->GetMainCamera()->SetNearPlane(0.1f);
	world->GetMainCamera()->SetFarPlane(500.0f);
	world->GetMainCamera()->SetPitch(-15.0f);
	world->GetMainCamera()->SetYaw(315.0f);
	world->GetMainCamera()->SetPosition(Vector3(0, 0, 0));
	lockedObject = nullptr;
}

void TutorialGame::InitWorld() {
	world->ClearAndErase();
	physics->Clear();
//	BridgeConstraintTest();
	InitMixedGridWorld(5, 5, 3.5f, 3.5f);
	InitGameExamples();
	InitDefaultFloor();
	//testStateObject = AddStateObjectToWorld(Vector3(10, 10, 5));

}

void TutorialGame::BridgeConstraintTest() {
	Vector3 cubeSize = Vector3(8, 8, 8);

	float invCubeMass = 5;
	int numLinks = 10;
	float maxDistance = 30;
	float cubeDistance = 20;

	Vector3 startPos = Vector3(150, 50, 0);

	GameObject* start = AddCubeToWorld(startPos + Vector3(0, 0, 0), cubeSize, 0);

	GameObject* end = AddCubeToWorld(startPos + Vector3((numLinks + 2) * cubeDistance, 0, 0), cubeSize, 0);

	GameObject* previous = start;

	for (size_t i = 0; i < numLinks; i++)
	{
		GameObject* block = AddCubeToWorld(startPos + Vector3((i + 1) * cubeDistance, 0, 0), cubeSize, invCubeMass);

		PositionConstraint* constraint = new PositionConstraint(previous, block, maxDistance);
		world->AddConstraint(constraint);
		previous = block;
	}
	PositionConstraint* constraint = new PositionConstraint(previous, end, maxDistance);
	world->AddConstraint(constraint);
}

/*

A single function to add a large immoveable cube to the bottom of our world

*/
GameObject* TutorialGame::AddFloorToWorld(const Vector3& position) {
	GameObject* floor = new GameObject();

	Vector3 floorSize = Vector3(100, 2, 100);
	AABBVolume* volume = new AABBVolume(floorSize);
	floor->SetBoundingVolume((CollisionVolume*)volume);
	floor->GetTransform()
		.SetScale(floorSize * 2)
		.SetPosition(position);

	floor->SetRenderObject(new RenderObject(&floor->GetTransform(), cubeMesh, basicTex, basicShader));
	floor->SetPhysicsObject(new PhysicsObject(&floor->GetTransform(), floor->GetBoundingVolume()));

	floor->GetPhysicsObject()->SetInverseMass(0);
	floor->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(floor);

	return floor;
}

/*

Builds a game object that uses a sphere mesh for its graphics, and a bounding sphere for its
rigid body representation. This and the cube function will let you build a lot of 'simple'
physics worlds. You'll probably need another function for the creation of OBB cubes too.

展示了创建一个新的游戏目标的基本过程
*/
GameObject* TutorialGame::AddSphereToWorld(const Vector3& position, float radius, float inverseMass) {
	GameObject* sphere = new GameObject("Sphere");

	Vector3 sphereSize = Vector3(radius, radius, radius);
	SphereVolume* volume = new SphereVolume(radius);
	sphere->SetBoundingVolume((CollisionVolume*)volume);
	sphere->GetTransform()
		.SetScale(sphereSize)
		.SetPosition(position);

	sphere->SetRenderObject(new RenderObject(&sphere->GetTransform(), sphereMesh, basicTex, basicShader));//如果你想看到这个物体就需要把他加入render队列
	sphere->SetPhysicsObject(new PhysicsObject(&sphere->GetTransform(), sphere->GetBoundingVolume()));//如果要使用物理计算就需要一个BoundingVolume和加入物理队列

	sphere->GetPhysicsObject()->SetInverseMass(inverseMass);
	sphere->GetPhysicsObject()->InitSphereInertia();

	world->AddGameObject(sphere);

	return sphere;
}

GameObject* TutorialGame::AddCapsuleToWorld(const Vector3& position, float halfHeight, float radius, float inverseMass) {
	GameObject* capsule = new GameObject();

	CapsuleVolume* volume = new CapsuleVolume(halfHeight, radius);
	capsule->SetBoundingVolume((CollisionVolume*)volume);

	capsule->GetTransform()
		.SetScale(Vector3(radius * 2, halfHeight, radius * 2))
		.SetPosition(position);

	capsule->SetRenderObject(new RenderObject(&capsule->GetTransform(), capsuleMesh, basicTex, basicShader));
	capsule->SetPhysicsObject(new PhysicsObject(&capsule->GetTransform(), capsule->GetBoundingVolume()));

	capsule->GetPhysicsObject()->SetInverseMass(inverseMass);
	capsule->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(capsule);

	return capsule;
}

GameObject* TutorialGame::AddCubeToWorld(const Vector3& position, Vector3 dimensions, float inverseMass) {
	GameObject* cube = new GameObject("Cube");

	AABBVolume* volume = new AABBVolume(dimensions);

	cube->SetBoundingVolume((CollisionVolume*)volume);

	cube->GetTransform()
		.SetPosition(position)
		.SetScale(dimensions * 2);

	cube->SetRenderObject(new RenderObject(&cube->GetTransform(), cubeMesh, basicTex, basicShader));
	cube->SetPhysicsObject(new PhysicsObject(&cube->GetTransform(), cube->GetBoundingVolume()));

	cube->GetPhysicsObject()->SetInverseMass(inverseMass);
	cube->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(cube);

	return cube;
}

void TutorialGame::InitSphereGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing, float radius) {
	for (int x = 0; x < numCols; ++x) {
		for (int z = 0; z < numRows; ++z) {
			Vector3 position = Vector3(x * colSpacing, 10.0f, z * rowSpacing);
			AddSphereToWorld(position, radius, 1.0f);
		}
	}
	AddFloorToWorld(Vector3(0, -2, 0));
}

void TutorialGame::InitMixedGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing) {
	float sphereRadius = 1.0f;
	Vector3 cubeDims = Vector3(1, 1, 1);

	for (int x = 0; x < numCols; ++x) {
		for (int z = 0; z < numRows; ++z) {
			Vector3 position = Vector3(x * colSpacing, 10.0f, z * rowSpacing);

			if (rand() % 2) {
				AddCubeToWorld(position, cubeDims);
			}
			else {
				AddSphereToWorld(position, sphereRadius);
			}
		}
	}
}

void TutorialGame::InitCubeGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing, const Vector3& cubeDims) {
	for (int x = 1; x < numCols + 1; ++x) {
		for (int z = 1; z < numRows + 1; ++z) {
			Vector3 position = Vector3(x * colSpacing, 10.0f, z * rowSpacing);
			AddCubeToWorld(position, cubeDims, 1.0f);
		}
	}
}

void TutorialGame::InitDefaultFloor() {
	AddFloorToWorld(Vector3(0, -2, 0));
}

void TutorialGame::InitGameExamples() {
	localPlayer=dynamic_cast<NCL::CSC8599::Player*>(AddPlayerToWorld(Vector3(-10, 5, 0)));
	_monster= dynamic_cast<NCL::CSC8599::Monster*>(AddMonsterToWorld(Vector3(-50, 8, 50)));
	//AddDragonToWorld(Vector3(-50, 10, 0));
	_pet= dynamic_cast<NCL::CSC8599::Pet*>(AddPetToWorld(Vector3(-15, 5, 0), localPlayer));
	localPlayer->set_pet(_pet);
	//AddBonusToWorld(Vector3(10, 5, 0));
}

GameObject* TutorialGame::AddPlayerToWorld(const Vector3& position) {
	float meshSize = 3.0f;
	float inverseMass = 0.5f;
	Vector3 offset = Vector3(-4.5 * meshSize, 1 * meshSize, -9.5 * meshSize);
	//GameObject* character = new GameObject();
	//Character* character = new Character();
	const auto character = new NCL::CSC8599::Player();

	AABBVolume* volume = new AABBVolume(Vector3(0.3f, 0.85f, 0.3f) * meshSize);

	character->SetBoundingVolume((CollisionVolume*)volume);

	character->GetTransform()
		.SetScale(Vector3(meshSize, meshSize, meshSize))
		.SetPosition(position);

	
	character->SetRenderObject(new RenderObject(&character->GetTransform(), PlayerMesh, PlayerTex, basicShader,offset));
	
	character->SetPhysicsObject(new PhysicsObject(&character->GetTransform(), character->GetBoundingVolume()));

	character->GetPhysicsObject()->SetInverseMass(inverseMass);
	character->GetPhysicsObject()->InitSphereInertia();

	world->AddGameObject(character);

	//lockedObject = character;

	return character;
}

GameObject* TutorialGame::AddMonsterToWorld(const Vector3& position) {
	float meshSize =6.0f;
	float inverseMass = 0.5f;
	Vector3 offset = Vector3(4*meshSize, 2 * meshSize, -4.5 * meshSize);
	auto* character = new Monster();

	AABBVolume* volume = new AABBVolume(Vector3(0.3f, 0.9f, 0.3f) * meshSize);
	character->SetBoundingVolume((CollisionVolume*)volume);

	character->GetTransform()
		.SetScale(Vector3(meshSize, meshSize, meshSize))
		.SetPosition(position);

	character->SetRenderObject(new RenderObject(&character->GetTransform(),
		MonsterMesh, MonsterTex, basicShader,offset));

	character->SetPhysicsObject(new PhysicsObject(&character->GetTransform(), character->GetBoundingVolume()));

	character->GetPhysicsObject()->SetInverseMass(inverseMass);
	character->GetPhysicsObject()->InitSphereInertia();

	world->AddGameObject(character);

	return character;
}

GameObject* NCL::CSC8503::TutorialGame::AddDragonToWorld(const Vector3& position, Character* owner)
{
	float meshSize = 3.0f;
	float inverseMass = 0.5f;
	Vector3 offset = Vector3(-7 * meshSize,  -7* meshSize, -5 * meshSize);
	auto* character = new Dragon(owner);

	AABBVolume* volume = new AABBVolume(Vector3(0.3f, 0.9f, 0.3f) * meshSize);
	character->SetBoundingVolume((CollisionVolume*)volume);

	character->GetTransform()
		.SetScale(Vector3(meshSize, meshSize, meshSize))
		.SetPosition(position);

	character->SetRenderObject(new RenderObject(&character->GetTransform(),
		redDragonMesh, redDragonTex, basicShader,offset));

	character->SetPhysicsObject(new PhysicsObject(&character->GetTransform(), character->GetBoundingVolume()));

	character->GetPhysicsObject()->SetInverseMass(inverseMass);
	character->GetPhysicsObject()->InitSphereInertia();

	world->AddGameObject(character);

	return character;
}

GameObject* TutorialGame::AddPetToWorld(const Vector3& position, Character* owner)
{
	float meshSize = 3.0f;
	Vector3 offset = Vector3(-4.5* meshSize,2*meshSize, -9.5 * meshSize);
	auto pet = new Pet(owner);

	SphereVolume* volume = new SphereVolume(0.25f);
	pet->SetBoundingVolume((CollisionVolume*)volume);
	pet->GetTransform()
		.SetScale(Vector3(meshSize, meshSize, meshSize))
		.SetPosition(position);

	pet->SetRenderObject(new RenderObject(&pet->GetTransform(), PetMesh, PetTex, basicShader,offset));
	pet->SetPhysicsObject(new PhysicsObject(&pet->GetTransform(), pet->GetBoundingVolume()));

	pet->GetPhysicsObject()->SetInverseMass(1.0f);
	pet->GetPhysicsObject()->InitSphereInertia();

	world->AddGameObject(pet);

	return pet;
}

GameObject* TutorialGame::AddBonusToWorld(const Vector3& position) {
	GameObject* apple = new GameObject();

	SphereVolume* volume = new SphereVolume(0.25f);
	apple->SetBoundingVolume((CollisionVolume*)volume);
	apple->GetTransform()
		.SetScale(Vector3(0.25, 0.25, 0.25))
		.SetPosition(position);

	apple->SetRenderObject(new RenderObject(&apple->GetTransform(), bonusMesh, nullptr, basicShader));
	apple->SetPhysicsObject(new PhysicsObject(&apple->GetTransform(), apple->GetBoundingVolume()));

	apple->GetPhysicsObject()->SetInverseMass(1.0f);
	apple->GetPhysicsObject()->InitSphereInertia();

	world->AddGameObject(apple);

	return apple;
}

StateGameObject* NCL::CSC8503::TutorialGame::AddStateObjectToWorld(const Vector3& position)
{
	StateGameObject* apple = new StateGameObject();

	SphereVolume* volume = new SphereVolume(0.25f);
	apple->SetBoundingVolume((CollisionVolume*)volume);
	apple->GetTransform()
		.SetScale(Vector3(0.25, 0.25, 0.25))
		.SetPosition(position);

	apple->SetRenderObject(new RenderObject(&apple->GetTransform(), bonusMesh, nullptr, basicShader));
	apple->SetPhysicsObject(new PhysicsObject(&apple->GetTransform(), apple->GetBoundingVolume()));

	apple->GetPhysicsObject()->SetInverseMass(1.0f);
	apple->GetPhysicsObject()->InitSphereInertia();

	world->AddGameObject(apple);

	return apple;
}

void NCL::CSC8503::TutorialGame::initStateMachine()
{
	game_state_machine = new NCL::CSC8599::StateMachine("init",
		new NCL::CSC8599::State([this](float dt)->void
		{
			MoveCameraToMenu();
			std::vector<std::string> text;
			text.emplace_back("Scenarios A and B");
			text.emplace_back("Scenarios C");

			if (selected < 0)selected = 0;
			if (selected >= text.size())selected = text.size() - 1;
			if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::DOWN)) {
				selected++;
			}
			if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::UP)) {
				selected--;
			}
			if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::RETURN)) {
				switch (selected)
				{
				case 0:
					gameReset(0);
					break;
				case 1:
					gameReset(1);
					break;
				default:
					break;
				}
			}
			for (int i = 0; i < text.size(); ++i)
			{
				if (i == selected)
					renderer->DrawString(text[i], Vector2(45, 20 * (i + 1)), Vector4(1, 0, 1, 1));
				else
					renderer->DrawString(text[i], Vector2(45, 20 * (i + 1)));
			}
		}));
	game_state_machine->AddComponent("running", new NCL::CSC8599::State([this](float dt)->void
		{
			if (!inSelectionMode) {
				world->GetMainCamera()->UpdateCamera(dt);
			}

			UpdateKeys();

			if (useGravity) {
				Debug::Print("(G)ravity on", Vector2(5, 95));
			}
			else {
				Debug::Print("(G)ravity off", Vector2(5, 95));
			}

			SelectObject();
			//MoveSelectedObject();
			//physics->Update(dt);

			if (lockedObject != nullptr) {
				Vector3 objPos = lockedObject->GetTransform().GetPosition();
				Vector3 camPos = objPos + lockedOffset;

				Matrix4 temp = Matrix4::BuildViewMatrix(camPos, objPos, Vector3(0, 1, 0));

				Matrix4 modelMat = temp.Inverse();

				Quaternion q(modelMat);
				Vector3 angles = q.ToEuler(); //nearly there now!

				world->GetMainCamera()->SetPosition(camPos);
				world->GetMainCamera()->SetPitch(angles.x);
				world->GetMainCamera()->SetYaw(angles.y);

				//Debug::DrawAxisLines(lockedObject->GetTransform().GetMatrix(), 2.0f);
			}

			world->UpdateWorld(dt);

			if(useDebugSM)
			{
				Debug::Print("(F4)Debug state machine on", Vector2(5, 5));
				debug_state_machine->Update(dt);
			}else
			{
				Debug::Print("(F4)Debug state machine off", Vector2(5, 5));
			}
		}));

	game_state_machine->AddComponent("end", new NCL::CSC8599::State([this](float dt)->void
		{
			if(win+lose==total)
			{
				renderer->DrawString("win:" + std::to_string(win), Vector2(45, 50));
				renderer->DrawString("lose:" + std::to_string(lose), Vector2(45, 55));
				renderer->DrawString("Press enter to 'space' to the main menu", Vector2(25, 60));
				if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::SPACE))
				{
					EventSystem::getInstance()->PushEvent("GameInit", 0);
				}
			}
			else
			{
				EventSystem::getInstance()->PushEvent("GameReset", 0);
			}
			
		}));

	game_state_machine->AddTransition(new CSC8599::StateTransition(
		game_state_machine->GetComponent("init"),
		game_state_machine->GetComponent("running"),
		[this](EVENT* p_event)->bool
		{
			InitCamera();
			return true;
		},
		"GameStart"
	));

	game_state_machine->AddTransition(new CSC8599::StateTransition(
		game_state_machine->GetComponent("end"),
		game_state_machine->GetComponent("running"),
		[this](EVENT* p_event)->bool
		{
			gameReset(0);
			localPlayer->set_user_controller(new PlayerAIController(localPlayer));
			return true;
		},
		"GameReset"
			));

	game_state_machine->AddTransition(new CSC8599::StateTransition(
		game_state_machine->GetComponent("end"),
		game_state_machine->GetComponent("init"),
		[this](EVENT* p_event)->bool
		{
			lose = 0;
			win = 0;
			return true;
		},
		"GameInit"
			));

	game_state_machine->AddTransition(new CSC8599::StateTransition(
		game_state_machine->GetComponent("running"),
		game_state_machine->GetComponent("end"),
		[this](EVENT* p_event)->bool
		{
			if (EventSystem::getInstance()->HasHappened("player_die"))
			{
				lose++;
				return true;
			}
			else if (EventSystem::getInstance()->HasHappened("MonsterDie"))
			{
				win++;
				return true;
			}
			else
				return false;
				
		},
		""
			));

	debug_state_machine = new DebugStateMachine();

	auto formula = ltlf::Box(ltlf::Implies(ltlf::Act("player_over_threat"),
		ltlf::Next(ltlf::Act("pet_taunt"))));
	auto sigmaAll = std::unordered_set<std::string>{ "player_over_threat", "pet_taunt" ,"other" };
	auto DebugA = StateMachineParser::getInstance()->parse(formula, sigmaAll);

	formula = ltlf::Box(ltlf::Implies(ltlf::Act("player_die"),
		ltlf::Next(ltlf::Act("pet_die"))));
	sigmaAll = std::unordered_set<std::string>{ "player_die", "pet_die" ,"other"};
	auto DebugB = StateMachineParser::getInstance()->parse(formula, sigmaAll);


	formula = ltlf::Box(ltlf::Implies(ltlf::Act("summon_dragon"),
		ltlf::And(ltlf::Diamond(ltlf::Act("dragon_die")),
			ltlf::Until(ltlf::Act("dragon_die", true), ltlf::Act("arrival"))
		)));
	sigmaAll = std::unordered_set<std::string>{ "init", "summon_dragon", "arrival","dragon_die" ,"other"};
	auto DebugC = StateMachineParser::getInstance()->parse(formula, sigmaAll);

	debug_state_machine->AddComponent("DebugA", DebugA);
	debug_state_machine->AddComponent("DebugB", DebugB);
	debug_state_machine->AddComponent("DebugC", DebugC);

}

void NCL::CSC8503::TutorialGame::gameReset(int model)
{
	//InitCamera();
	EventSystem::getInstance()->Reset();
	initEventHandler();
	InitWorld();
	if(model==0)
	{
		localPlayer->set_user_controller(new PlayerAIController(localPlayer));
		localPlayer->GetTransform().SetPosition(Vector3(-50, 8, 35));
		_pet->GetTransform().SetPosition(Vector3(-50, 8, 70));
		_monster->useStateMachine = false;
	}else if(model==1)
	{
		localPlayer->set_user_controller(new PlayerController());
	}
	EventSystem::getInstance()->PushEvent("GameStart", 0);
}

void NCL::CSC8503::TutorialGame::initEventHandler()
{
	EventSystem::getInstance()->RegisterEventHandler("summon_dragon", [this](EVENT* p_event)->bool
	{
		int id = stoi(p_event->vArg[0]);
		auto monster = dynamic_cast<Monster*>(world->find_game_object(id));
		_dragon= dynamic_cast<Dragon*>(AddDragonToWorld(Vector3(-50, 10, 0), monster));
		monster->set_pet(_dragon);
		return true;
	});
	EventSystem::getInstance()->RegisterEventHandler("fix_DebugC", [this](EVENT* p_event)->bool
		{
			_monster->immortal = false;
			return true;
		});
}

/*

Every frame, this code will let you perform a raycast, to see if there's an object
underneath the cursor, and if so 'select it' into a pointer, so that it can be
manipulated later. Pressing Q will let you toggle between this behaviour and instead
letting you move the camera around.

*/
bool TutorialGame::SelectObject() {
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::Q)) {
		inSelectionMode = !inSelectionMode;
		if (inSelectionMode) {
			Window::GetWindow()->ShowOSPointer(true);
			Window::GetWindow()->LockMouseToWindow(false);
		}
		else {
			Window::GetWindow()->ShowOSPointer(false);
			Window::GetWindow()->LockMouseToWindow(true);
		}
	}
	if (inSelectionMode) {
		renderer->DrawString("Press Q to change to camera mode!", Vector2(5, 85));

		if (Window::GetMouse()->ButtonDown(NCL::MouseButtons::LEFT)) {
			if (selectionObject) {	//set colour to deselected;
				selectionObject->GetRenderObject()->SetColour(Vector4(1, 1, 1, 1));
				selectionObject = nullptr;
				lockedObject = nullptr;
			}

			Ray ray = CollisionDetection::BuildRayFromMouse(*world->GetMainCamera());//从鼠标位置发出一道射线

			//从场景的物体发出另外一束光线来确定谁从前方看到选择的物体

			RayCollision closestCollision;
			if (world->Raycast(ray, closestCollision, true)) {
				selectionObject = (GameObject*)closestCollision.node;
				selectionObject->GetRenderObject()->SetColour(Vector4(0, 1, 0, 1));

				//可以计算出在点击物体前方的正方体 因为其他体积还没有写碰撞函数 所以无法实现
				/*Ray ray_ = Ray(selectionObject->GetTransform().GetPosition(),Vector3(0,0,-1));

				if (world->Raycast(ray_, closestCollision, true)) {
					selectionObject = (GameObject*)closestCollision.node;
					selectionObject->GetRenderObject()->SetColour(Vector4(1, 0, 0, 1));
				}*/
				return true;
			}
			else {
				return false;
			}
		}
	}
	else {
		renderer->DrawString("Press Q to change to select mode!", Vector2(5, 85));
	}

	if (lockedObject) {
		renderer->DrawString("Press L to unlock object!", Vector2(5, 80));
	}

	else if (selectionObject) {
		renderer->DrawString("Press L to lock selected object object!", Vector2(5, 80));
	}

	if (Window::GetKeyboard()->KeyPressed(NCL::KeyboardKeys::L)) {
		if (selectionObject) {
			if (lockedObject == selectionObject) {
				lockedObject = nullptr;
			}
			else {
				lockedObject = selectionObject;
			}
		}
	}

	return false;
}

/*
If an object has been clicked, it can be pushed with the right mouse button, by an amount
determined by the scroll wheel. In the first tutorial this won't do anything, as we haven't
added linear motion into our physics system. After the second tutorial, objects will move in a straight
line - after the third, they'll be able to twist under torque aswell.
*/
void TutorialGame::MoveSelectedObject() {
	renderer->DrawString("Click Force:" + std::to_string(forceMagnitude),
		Vector2(10, 20));
	forceMagnitude += Window::GetWindow()->GetMouse()->GetWheelMovement() * 100.0f;//使用鼠标滚轮来控制力的量

	if (!selectionObject) {
		return;
	}

	if (Window::GetMouse()->ButtonPressed(NCL::MouseButtons::RIGHT)) {//鼠标右键对选中的物体施加力
		Ray ray = CollisionDetection::BuildRayFromMouse(*world->GetMainCamera());

		RayCollision closestCollision;
		if (world->Raycast(ray, closestCollision, true)) {
			if (closestCollision.node == selectionObject) {
				//selectionObject->GetPhysicsObject()->AddForce(ray.GetDirection() * forceMagnitude);
				selectionObject->GetPhysicsObject()->AddForceAtPosition(ray.GetDirection() * forceMagnitude, closestCollision.collidedAt);
			}
		}
	}
}