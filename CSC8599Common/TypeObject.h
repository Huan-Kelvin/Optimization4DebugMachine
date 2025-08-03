#pragma once
#include "SharedStateMachine.h"
#include "../CSC8503/CSC8503Common/GameWorld.h"
#include "TestObj.h"

namespace NCL {
    namespace CSC8599 {
		class ExtendCharacter;
        class TypeObject {
        public:
            TypeObject() {
                instances.push_back(this);
            }

            virtual ~TypeObject() {
                auto it = std::find(instances.begin(), instances.end(), this);
                if (it != instances.end())
                    instances.erase(it);
            }

            virtual void Update(float dt) = 0;

            static void UpdateAll(float dt) {
                for (auto obj : instances) {
                    obj->Update(dt);
                }
            }

            virtual void Reset() = 0;

            static void ResetAll() {
                for (auto obj : instances) {
                    obj->Reset();
                }
            }
        private:
            static std::vector<TypeObject*> instances;
        };

        class CharacterType : public TypeObject {
        public:
            virtual ~CharacterType() = default;

            static SharedStateMachine* GetStateMachine() {
                return state_machine;
            }

            void Update(float dt) override {
                state_machine->Update(dt);
            }

            virtual void Reset() override {
                if (state_machine) {
                    delete state_machine;
                    state_machine = nullptr;
                }
            }

            void showHUD(Transform trans, std::string text, const float height = 7, Vector4 color = Vector4(1, 1, 1, 1))
            {
                auto viewMatrix = GameWorld::Get()->GetMainCamera()->BuildViewMatrix();
                auto projectMatrix = GameWorld::Get()->GetMainCamera()->BuildProjectionMatrix();

                Matrix4 local = trans.GetMatrix();
                local.SetPositionVector({ 0, 0, 0 });

                Vector3 up = local * Vector4(0, 1, 0, 1.0f);
                Vector3 left = local * Vector4(-1, 0, 0, 1.0f);
                Vector3 worldPos = trans.GetPosition();
                Vector3 clip = projectMatrix * viewMatrix * worldPos;
                Vector2 canvas;
                canvas.x = (clip.x + 2.0f) * 25.0f - 1.0f * text.size();
                canvas.y = (1.0f - clip.y) * 50.0f - height;
                Debug::Print(text, canvas, color);
            }

            float GetMaxHealth() const { return maxHealth; }

            virtual void BlockTrans(ExtendCharacter* cha) { 
                state_machine->BlockObject((GameObject*)cha); 
            }

        protected:
            CharacterType() = default;

            virtual void InitStateMachine() = 0;

            static SharedStateMachine* state_machine;
            float maxHealth = 10;
        };

        class TestObjType : public CharacterType {
        public:
            TestObjType() {
                maxHealth = 100;
                Reset();
            }
            TestObjType(const TestObjType&) = delete;
            TestObjType& operator=(const TestObjType&) = delete;

            static TestObjType& Instance() {
                static TestObjType instance;
                return instance;
            }

            void Update(float dt) override {
                CharacterType::Update(dt);
            }
            void Reset() override {
                CharacterType::Reset();
                InitStateMachine();
            }

            void takeDamage(TestObj& obj, float amount, GameObject* source = nullptr) { obj.HealthChange(-amount); }

        protected:
            void InitStateMachine() override;

        private:
            CSC8599::StateTransition* t1;
            CSC8599::StateTransition* t2;
            CSC8599::StateTransition* t3;
        };

        class DeviceType : public CharacterType
        {
        public:
            DeviceType() {
                maxHealth = 100;
                Reset();
            }
            DeviceType(const DeviceType&) = delete;
            DeviceType& operator=(const DeviceType&) = delete;

            static DeviceType& Instance() {
                static DeviceType instance;
                return instance;
			}
            void Update(float dt) override {
                CharacterType::Update(dt);
            }
            void Reset() override {
                CharacterType::Reset();
                InitStateMachine();
            }
			//void takeDamage(TestObj& obj, float amount, GameObject* source = nullptr) { obj.HealthChange(-amount); }

        protected:
            void InitStateMachine() override;

        private:

        };
    }
}

