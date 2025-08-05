#pragma once
#include "GameTechRenderer.h"
#include "../CSC8503Common/PhysicsSystem.h"
#include "StateGameObject.h"
#include "../../CSC8599Common/EventSystem.h"
#include "../../CSC8599Common/DebugStateMachine.h"
#include "../../CSC8599Common/AdaptiveDebugSystem.h"

#include "../../CSC8599Common/TestObj.h"
#include "../../CSC8599Common/SharedStateMachine.h"
#include "../../CSC8599Common/ExtendCharacter.h"

namespace NCL
{
	namespace CSC8599
	{
		class Dragon;
		class Pet;
		class Monster;
		class StateMachine;
		class Character;
		class Player;

		class TestObj;
	}
}

/*
���ǵ������Ǳ�֤��������Ⱦǰ����ƶ���������㶼����ȷ�ġ����������Ŀ�ľ���Ϊ�˾������Ϸ�߼�����ҵ��������������
*/
using namespace NCL::CSC8599;
namespace NCL {
	namespace CSC8503 {
		class TutorialGame		{
		public:
			TutorialGame();
			virtual ~TutorialGame();
			/// <summary>
			/// һ��whileѭ��������Ϸ
			/// </summary>
			/// <param name="dt">ʱ�䲽��</param>
			virtual void UpdateGame(float dt);

			bool running = true;

		protected:
			void InitialiseAssets();

			void InitCamera();
			void MoveCameraToMenu();

			void UpdateKeys();

			void InitWorld(int idx);

			void InitGameExamples(int idx);

			void InitSphereGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing, float radius);
			void InitMixedGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing);
			void InitCubeGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing, const Vector3& cubeDims);
			void InitDefaultFloor();
			void BridgeConstraintTest();
	
			bool SelectObject();
			void MoveSelectedObject();
			void DebugObjectMovement();
			void LockedObjectMovement();

			GameObject* AddFloorToWorld(const Vector3& position);
			GameObject* AddSphereToWorld(const Vector3& position, float radius, float inverseMass = 10.0f);
			GameObject* AddCubeToWorld(const Vector3& position, Vector3 dimensions, float inverseMass = 10.0f);
			
			GameObject* AddCapsuleToWorld(const Vector3& position, float halfHeight, float radius, float inverseMass = 10.0f);

			GameObject* AddPlayerToWorld(const Vector3& position);
			GameObject* AddMonsterToWorld(const Vector3& position);
			GameObject* AddDragonToWorld(const Vector3& position, Character* owner);
			GameObject* AddPetToWorld(const Vector3& position,Character* owner);
			GameObject* AddBonusToWorld(const Vector3& position);

			GameObject* AddTestObjToWorld(string name, const Vector3& position);

			StateGameObject* AddStateObjectToWorld(const Vector3& position);
			StateGameObject* testStateObject;

			GameTechRenderer*	renderer;
			PhysicsSystem*		physics;
			GameWorld*			world;

			bool useGravity;
			bool inSelectionMode;

			float		forceMagnitude;

			GameObject* selectionObject = nullptr;

			OGLMesh*	capsuleMesh = nullptr;
			OGLMesh*	cubeMesh	= nullptr;
			OGLMesh*	sphereMesh	= nullptr;
			OGLTexture* basicTex	= nullptr;
			OGLShader*	basicShader = nullptr;

			//Coursework Meshes
			OGLMesh*	charMeshA	= nullptr;
			OGLMesh*	charMeshB	= nullptr;
			OGLMesh*	enemyMesh	= nullptr;
			OGLMesh*	bonusMesh	= nullptr;
			//Game Meshes
			OGLMesh* redDragonMesh = nullptr;
			OGLTexture* redDragonTex = nullptr;
			OGLMesh* MonsterMesh = nullptr;
			OGLTexture* MonsterTex = nullptr;
			OGLMesh* PlayerMesh = nullptr;
			OGLTexture* PlayerTex = nullptr;
			OGLMesh* PetMesh = nullptr;
			OGLTexture* PetTex = nullptr;

			//Coursework Additional functionality	
			GameObject* lockedObject	= nullptr;
			Vector3 lockedOffset		= Vector3(0, 14, 20);
			void LockCameraToObject(GameObject* o) {
				lockedObject = o;
			}

			//DebugSM
			bool useDebugSM = false;
			DebugStateMachine* debug_state_machine = nullptr;

			DebugStateMachine* test_state_machine = nullptr;
			TestObj* test_obj = nullptr;
			ExtendCharacter* device = nullptr;
			ExtendCharacter* player = nullptr;
			ExtendCharacter* enemy = nullptr;
			vector<ExtendCharacter*> deviceList;

			//Game State Machine
			NCL::CSC8599::StateMachine* game_state_machine = nullptr;
			void initStateMachine();
			int selected = 0;

			NCL::CSC8599::Player* localPlayer = nullptr;
			NCL::CSC8599::Monster* _monster = nullptr;
			NCL::CSC8599::Pet* _pet = nullptr;
			NCL::CSC8599::Dragon* _dragon = nullptr;
			//test
			void gameReset(int model);
			int win = 0;
			int lose = 0;
			int total = 10;

			void initEventHandler();


			SharedStateMachine* shared1;
			SharedStateMachine* shared2;

			int curMode = -1;
			void initDebugStateMachine(vector<ExtendCharacter*> list, int ruleIdx = 0);
			void Clear();
			void UpdateSimulation(int idx);
			int curSimulation = -1;
			void ResetGame();
		};
	}
}

