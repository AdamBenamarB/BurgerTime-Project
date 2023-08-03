#include "PeterPepperComponent.h"

#include "GameObject.h"

void dae::PeterPepperComponent::Update(float deltaTime)
{
	HandleMovement(deltaTime);
	HandleCollision(deltaTime);
}

void dae::PeterPepperComponent::HandleMovement(float deltaTime)
{
	switch(m_State)
	{
	case State::idle:
		break;
	case State::left:
	{
		auto pos = m_Transform->GetWorldPosition();
		pos.x -= m_MovementSpeed * deltaTime;
		m_Transform->SetLocalPosition(pos);
		break;
	}
	case State::right:
	{
		auto pos = m_Transform->GetWorldPosition();
		pos.x += m_MovementSpeed * deltaTime;
		m_Transform->SetLocalPosition(pos);
		break;
	}
	}
}

void dae::PeterPepperComponent::HandleCollision(float)// deltaTime)
{
	
}


