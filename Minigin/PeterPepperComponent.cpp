#include "PeterPepperComponent.h"

#include <iostream>

#include "CollisionComponent.h"
#include "GameObject.h"
#include "AnimatedRenderComponent.h"
#include "PointsComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Tags.h"
#include "../BurgerTime/LadderComponent.h"
#include "../BurgerTime/PlatformComponent.h"

namespace dae
{
	class PlatformComponent;
	class LadderComponent;
}

dae::PeterPepperComponent::PeterPepperComponent(GameObject* owner) :Component(owner)
{
	m_Transform = owner->GetTransform();
	m_CollisionComp = owner->GetComponent<CollisionComponent>();
}


void dae::PeterPepperComponent::Update(float deltaTime)
{
	HandleMovement(deltaTime);
	HandleAnim(deltaTime);
}

void dae::PeterPepperComponent::HandleMovement(float deltaTime)
{
	switch(m_State)
	{
	case State::idle:
		break;
	case State::left:
		{
		for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			auto colcomp = object->GetComponent<CollisionComponent>();
			if (colcomp)
			{
				if (m_CollisionComp->IsOverlapping(object.get()))
				{
					if (object->GetTag() == Tag::platform)
					{
						auto platcomp = object->GetComponent<PlatformComponent>();
						if (!platcomp->OnLeft(GetOwner()) && platcomp->InRange(GetOwner()))
						{
							auto pos = m_Transform->GetWorldPosition();
							pos.x -= m_MovementSpeed * deltaTime;
							pos.y = platcomp->GetFloorY();
							m_Transform->SetLocalPosition(pos);
							break;
						}

					}
				}
			}
		}
		
		break;
		}
	case State::right:
		{
		for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			auto colcomp = object->GetComponent<CollisionComponent>();
			if (colcomp)
			{
				if (m_CollisionComp->IsOverlapping(object.get()))
				{
					if (object->GetTag() == Tag::platform)
					{
						auto platcomp = object->GetComponent<PlatformComponent>();
						if(!platcomp->OnRight(GetOwner()) && platcomp->InRange(GetOwner()))
						{
							auto pos = m_Transform->GetWorldPosition();
							pos.x += m_MovementSpeed * deltaTime;
							pos.y = platcomp->GetFloorY();
							m_Transform->SetLocalPosition(pos);
							break;
						}
						
					}
				}
			}
		}
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
					if (object->GetTag() == Tag::ladder)
						{
						auto laddercomp = object->GetComponent<LadderComponent>();
						if (!laddercomp->OnBottom(GetOwner()) && laddercomp->InRange(GetOwner()))
						{
							auto pos = m_Transform->GetWorldPosition();
							pos.y += m_MovementSpeed * deltaTime;
							pos.x = object->GetTransform()->GetWorldPosition().x;
							m_Transform->SetLocalPosition(pos);
							break;
						}
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
					if (object->GetTag() == Tag::ladder)
					{
						auto laddercomp = object->GetComponent<LadderComponent>();
						if (!laddercomp->OnTop(GetOwner()) && laddercomp->InRange(GetOwner()))
						{
							auto pos = m_Transform->GetWorldPosition();
							pos.y -= m_MovementSpeed * deltaTime;
							pos.x = object->GetTransform()->GetWorldPosition().x;
							m_Transform->SetLocalPosition(pos);
							break;
						}
					}
				}
			}
		}
		break;
	}
	}
}

void dae::PeterPepperComponent::InitAnimation(AnimatedRenderComponent* comp)
{
	if (comp == nullptr)
		return;

	m_Anim = comp;

	m_Idle = m_Anim->AddClip(1, false);
	m_RunLeft = m_Anim->AddClip(3, true);
	m_RunRight = m_Anim->AddClip(3, true);
	m_Climb = m_Anim->AddClip(3, true);
	m_ClimbDown = m_Anim->AddClip(3, true);
}

void dae::PeterPepperComponent::HandleAnim(float deltaTime)
{
	switch (m_State)
	{
	case State::idle:
		m_Anim->SetClip(m_Idle);
		break;
	case State::left:
			m_Anim->SetClip(m_RunLeft);
		break;
	case State::right:
			m_Anim->SetClip(m_RunRight);
		break;
	case State::up:
			m_Anim->SetClip(m_Climb);
		break;
	case State::down:
			m_Anim->SetClip(m_ClimbDown);
		break;
	}
}

void dae::PeterPepperComponent::AddPoints(GameObject* go)
{
	Tag tag = go->GetTag();

	if (tag == Tag::hotdog)
		GetOwner()->GetComponent<PointsComponent>()->AddPoints(100);
	else if (tag == Tag::pickle)
		GetOwner()->GetComponent<PointsComponent>()->AddPoints(200);
	else if (tag == Tag::egg)
		GetOwner()->GetComponent<PointsComponent>()->AddPoints(300);
}

void dae::PeterPepperComponent::AddPoints(int amt)
{
	GetOwner()->GetComponent<PointsComponent>()->AddPoints(amt);
}