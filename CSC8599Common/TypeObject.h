#pragma once
#include "SharedStateMachine.h"

namespace NCL {
    namespace CSC8599 {
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
                delete state_machine;
                state_machine = nullptr;
            }
        protected:
            CharacterType() = default;
            static SharedStateMachine* state_machine;
        };

        class TestObjType : public CharacterType {
        public:
            TestObjType() {
                InitStateMachine();
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

        private:
			CSC8599::StateTransition* t1;
			CSC8599::StateTransition* t2;
			CSC8599::StateTransition* t3;

            void InitStateMachine();
        };
	}
}

