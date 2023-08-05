#include "PeterPepperComponent.h"

#include <iostream>

#include "CollisionComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"

dae::PeterPepperComponent::PeterPepperComponent(GameObject* owner) :Component(owner)
{
	m_Transform = owner->GetTransform();
	m_CollisionComp = owner->GetComponent<CollisionComponent>();
}


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
	case State::down:
		{
		for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			auto colcomp = object->GetComponent<CollisionComponent>();
			if (colcomp)
			{
				if (m_CollisionComp->IsOverlapping(object.get()))
				{
					if (object->GetTag().compare("LADDER") == 0)
						{
						auto pos = m_Transform->GetWorldPosition();
						pos.y += m_MovementSpeed * deltaTime;
						m_Transform->SetLocalPosition(pos);
						}
				}
			}
		}
		break;
		}
	case State::up:
	{
		for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			auto colcomp = object->GetComponent<CollisionComponent>();
			if (colcomp)
			{
				if (m_CollisionComp->IsOverlapping(object.get()))
				{
					if (object->GetTag().compare("LADDER") == 0)
					{
						auto pos = m_Transform->GetWorldPosition();
						pos.y -= m_MovementSpeed * deltaTime;
						m_Transform->SetLocalPosition(pos);
					}
				}
			}
		}
		break;
	}
	}
}

void dae::PeterPepperComponent::HandleCollision(float)// deltaTime)
{
	for( auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
	{
		auto colcomp = object->GetComponent<CollisionComponent>();
		if(colcomp)
		{
			if(m_CollisionComp->IsOverlapping(object.get()))
			{

			}
		}
	}
}


