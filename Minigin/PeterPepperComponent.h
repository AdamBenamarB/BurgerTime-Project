#pragma once
#include "Component.h"
#include "GameObject.h"
#include "RenderComponent.h"

namespace dae {
	class AnimatedRenderComponent;
	class CollisionComponent;
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
        PeterPepperComponent(GameObject* owner);
        ~PeterPepperComponent(){}
        void Update(float deltaTime) override;
        void FixedUpdate(float) override{}

        void SetState(State state) { m_State = state; }//DO CHECK FOR LADDER WHEN UP DOWN, CHECK FOR FLOOR LEFT RIGHT

        void InitAnimation(AnimatedRenderComponent* comp);

        void Hit(){};
    private:
        float m_MovementSpeed = 50.f;
        Transform* m_Transform = nullptr;
        RenderComponent* m_RenderComp = nullptr;
        CollisionComponent* m_CollisionComp = nullptr;
        State m_State = State::idle;

        bool m_OnPlatform = false;
        bool m_OnLadder = false;

        //ANIM
        AnimatedRenderComponent* m_Anim{};


        int m_Idle{},
            m_RunLeft{},
            m_RunRight{},
            m_Climb{},
            m_ClimbDown{};

        void HandleMovement(float deltaTime);
        void HandleCollision(float deltaTime);
        void HandleAnim(float deltaTime);

        

    };
}
