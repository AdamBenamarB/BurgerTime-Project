#include "PlayerDogComponent.h"

#include <iostream>

#include "CollisionComponent.h"
#include "GameObject.h"
#include "AnimatedRenderComponent.h"
#include "EnemyComponent.h"
#include "PeterPepperComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "Tags.h"
#include "../BurgerTime/LadderComponent.h"
#include "../BurgerTime/PlatformComponent.h"
#include "../BurgerTime/GameInstance.h"

namespace dae
{
	class PlatformComponent;
	class LadderComponent;
}

dae::PlayerDogComponent::PlayerDogComponent(GameObject* owner) :Component(owner)
{
	Initialize();
}


void dae::PlayerDogComponent::Update(float deltaTime)
{
	HandleMovement(deltaTime);
	HandleAnim(deltaTime);
	HandleStun(deltaTime);
	CheckPeter();
}

void dae::PlayerDogComponent::HandleStun(float deltaTime)
{
	if (m_State == State::stunned)
	{
		m_StunElapsed += deltaTime;
		if (m_StunElapsed > m_StunTime)
		{
			ResetState();
			m_StunElapsed = 0;
		}
	}
}

void dae::PlayerDogComponent::HandleMovement(float deltaTime)
{
	if (m_State != State::stunned && m_State != State::falling)
	{
		switch (m_State)
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
							if (!platcomp->OnRight(GetOwner()) && platcomp->InRange(GetOwner()))
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
}

void dae::PlayerDogComponent::InitAnimation(AnimatedRenderComponent* comp)
{
	if (comp == nullptr)
		return;

	m_Anim = comp;

	m_RunLeft = m_Anim->AddClip(2, true);
	m_RunRight = m_Anim->AddClip(2, true);
	m_ClimbDown = m_Anim->AddClip(2, true);
	m_Climb = m_Anim->AddClip(2, true);
	m_Stunned = m_Anim->AddClip(2, false);
}

void dae::PlayerDogComponent::HandleAnim(float)
{
	switch (m_State)
	{
	case State::idle:
		m_Anim->SetClip(m_ClimbDown);
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
	case State::stunned:
		m_Anim->SetClip(m_Stunned);
		break;
	}
}

void dae::PlayerDogComponent::Stun()
{
	m_State = State::stunned;
}

void dae::PlayerDogComponent::CheckPeter()
{
	if(m_State != State::stunned && m_State != State::falling)
	for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
	{
		auto colcomp = object->GetComponent<CollisionComponent>();
		if (m_CollisionComp->IsOverlapping(object.get()))
		{
			if (colcomp)
				if (object->GetTag() == Tag::peter)
					object->GetComponent<PeterPepperComponent>()->Hit();
		}
		}
}

void dae::PlayerDogComponent::Initialize()
{
	m_Fall = dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/enemyfall.wav");
	m_CollisionComp = GetOwner()->GetComponent<CollisionComponent>();
	m_Transform = GetOwner()->GetTransform();
}


void dae::PlayerDogComponent::SetState(State state)
{
	if(m_State != State::falling && m_State != State::stunned)
	{
		m_State = state;
		if (state == State::falling)
			ServiceLocator::GetSoundSystem().Play(m_Fall, 128);
	}
	
}

void dae::PlayerDogComponent::ResetState()
{
	m_State = State::idle;
	m_StunElapsed = 0;
}
