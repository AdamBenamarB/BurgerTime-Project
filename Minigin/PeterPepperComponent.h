#pragma once
#include "Component.h"
#include "GameObject.h"
#include "RenderComponent.h"

namespace dae {
	class Transform;
	//class AnimatedRenderComponent;

    class PeterPepperComponent : public Component
    {
    public:
        enum class State
        {
            idle,
            left,
            right,
            up,
            down
        };
        PeterPepperComponent(GameObject* owner) :Component(owner) { m_Transform = owner->GetTransform(); }
        ~PeterPepperComponent(){}
        void Update(float deltaTime) override;
        void FixedUpdate(float) override{}

        void SetState(State state) { m_State = state; }
        
    private:
        float m_MovementSpeed = 50.f;
        Transform* m_Transform = nullptr;
        RenderComponent* m_RenderComp;
        State m_State = State::idle;
        void HandleMovement(float deltaTime);
        void HandleCollision(float deltaTime);


    };
}
