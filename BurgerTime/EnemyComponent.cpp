#include "EnemyComponent.h"

#include <iostream>

#include "AnimatedRenderComponent.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "LadderComponent.h"
#include "PeterPepperComponent.h"
#include "PlatformComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "Tags.h"

dae::EnemyComponent::EnemyComponent(GameObject* owner)
	:Component(owner)
{
	Initialize();
}

void dae::EnemyComponent::Update(float deltaTime)
{
	HandleMovement(deltaTime);
	HandleAnim();
	HandleStun(deltaTime);
}

void dae::EnemyComponent::HandleMovement(float deltaTime)
{
	if (m_State != State::falling && m_State != State::stunned)
	{
		glm::vec3 peterPos = m_Peter->GetTransform()->GetWorldPosition();
		glm::vec3 pos = GetOwner()->GetTransform()->GetWorldPosition();

		if (m_OnPlatform)
			m_Direction.y = peterPos.y - pos.y;

		//std::cout << "X: " << m_Direction.x << " Y: " << m_Direction.y << std::endl;

		for (auto& object : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			if (object->GetComponent<CollisionComponent>())
			{
				if (m_CollisionComp->IsOverlapping(object.get()))
				{
					if(object->GetTag() == Tag::peter || object->GetTag() == Tag::peterjr)
					{
						object->GetComponent<PeterPepperComponent>()->Hit();
					}
					if (object->GetTag() == Tag::ladder)
					{
						
						auto laddercomp = object->GetComponent<LadderComponent>();
						if (laddercomp->InRange(GetOwner()))
						{
							if (abs(m_Direction.y) > 8)
							{
								auto pos = m_Transform->GetWorldPosition();

								if (m_Direction.y > 0)
								{
									if (!laddercomp->OnBottom(GetOwner()))
									{
										pos.y += m_ClimbSpeed * deltaTime;
										m_State = State::down;
										pos.x = object->GetTransform()->GetWorldPosition().x;
										m_Transform->SetLocalPosition(pos);
										m_OnLadder = true;
										m_OnPlatform = false;
									}
									else
										CalcDirection();

								}
								if (m_Direction.y < 0)
								{
									if (!laddercomp->OnTop(GetOwner()))
									{
										pos.y -= m_ClimbSpeed * deltaTime;
										m_State = State::up;
										pos.x = object->GetTransform()->GetWorldPosition().x;
										m_Transform->SetLocalPosition(pos);
										m_OnLadder = true;
										m_OnPlatform = false;
									}
									else
										CalcDirection();
								}

							}
						}

					}
					if (object->GetTag() == Tag::platform)
					{
						auto pos = m_Transform->GetWorldPosition();
						auto platcomp = object->GetComponent<PlatformComponent>();
						if (m_Direction.x > 1)
						{
							if (platcomp->OnRight(GetOwner()))
							{
								pos.x -= m_Speed * deltaTime;
								m_State = State::left;
								pos.y = platcomp->GetFloorY();
								m_Transform->SetLocalPosition(pos);
								m_OnLadder = false;
								m_OnPlatform = true;
								CalcDirection();
							}
							pos.x += m_Speed * deltaTime;
							m_State = State::right;
						}
						if (m_Direction.x < -1)
						{
							if (platcomp->OnLeft(GetOwner()))
							{
								pos.x -= m_Speed * deltaTime;
								m_State = State::left;
								pos.y = platcomp->GetFloorY();
								m_Transform->SetLocalPosition(pos);
								m_OnLadder = false;
								m_OnPlatform = true;
								CalcDirection();
							}
							pos.x -= m_Speed * deltaTime;
							m_State = State::left;
						}
						pos.y = platcomp->GetFloorY();
						m_Transform->SetLocalPosition(pos);
						m_OnLadder = false;
						m_OnPlatform = true;
					}
					
				}
			}

		}
	}
}

void dae::EnemyComponent::SetState(State state)
{
	CalcDirection();
	m_State = state;
	if (state == State::falling)
		ServiceLocator::GetSoundSystem().Play(m_Fall, 128);
	
}

void dae::EnemyComponent::InitAnimation(AnimatedRenderComponent* animComp, std::string textureLoc)
{
	if (animComp == nullptr)
		return;
	animComp->SetTexture(textureLoc);

	m_Anim = animComp;

	m_RunLeft = m_Anim->AddClip(2, true);
	m_RunRight = m_Anim->AddClip(2, true);
	m_ClimbDown = m_Anim->AddClip(2, true);
	m_Climb = m_Anim->AddClip(2, true);
	m_Stunned = m_Anim->AddClip(2, false);
}

void dae::EnemyComponent::HandleAnim() const
{
	switch (m_State)
	{
	case State::left:
		m_Anim->SetClip(m_RunLeft);
		return;
	case State::right:
		m_Anim->SetClip(m_RunRight);
		return;
	case State::down:
		m_Anim->SetClip(m_ClimbDown);
		return;
	case State::up:
		m_Anim->SetClip(m_Climb);
		return;
	case State::stunned:
		m_Anim->SetClip(m_Stunned);
		return;
	}
}

void dae::EnemyComponent::SetPeter(GameObject* peterObj)
{
	if (!peterObj)
		return;
	m_Peter = peterObj;
	auto& pos = GetOwner()->GetTransform()->GetWorldPosition();
	auto& peterpos = m_Peter->GetTransform()->GetWorldPosition();

	m_Direction.x = peterpos.x - pos.x;
	m_Direction.y = peterpos.y - pos.y;
}

void dae::EnemyComponent::Kill()
{
	
	ServiceLocator::GetSoundSystem().Play(m_Hit, 100);
	m_State = State::dead;
}

void dae::EnemyComponent::Initialize()
{
	m_Hit = dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/enemyhit.wav");
	m_Fall = dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/enemyfall.wav");
	m_CollisionComp = GetOwner()->GetComponent<CollisionComponent>();
	m_Transform = GetOwner()->GetTransform();
}

void dae::EnemyComponent::HandleStun(float deltaTime)
{
	if (m_State == State::stunned)
	{
		m_StunElapsed += deltaTime;
		if (m_StunElapsed > m_StunTime)
		{
			m_State = State::left;
			m_StunElapsed = 0;
		}
	}
}

void dae::EnemyComponent::Stun()
{
	m_State = State::stunned;
}

void dae::EnemyComponent::CalcDirection()
{
	glm::vec3 peterPos = m_Peter->GetTransform()->GetWorldPosition();
	glm::vec3 pos = GetOwner()->GetTransform()->GetWorldPosition();

	m_Direction.y = peterPos.y - pos.y;
	m_Direction.x = peterPos.x - pos.x;
}
