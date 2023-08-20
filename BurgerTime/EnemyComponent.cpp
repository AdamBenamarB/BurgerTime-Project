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
		CalcDirection();
		if (m_MovementDir.x == 0 && m_MovementDir.y == 0)
			m_MovementDir = m_Direction;

		GameObject* platform = nullptr;
		GameObject* ladder = nullptr;
		glm::vec3 pos = GetOwner()->GetTransform()->GetWorldPosition();

		float platDist = 999;
		float ladderDist = 999;
		for (auto& object : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			if (object->GetComponent<CollisionComponent>())
			{
				if (m_CollisionComp->IsOverlapping(object.get()))
				{
					if (object->GetTag() == Tag::peter || object->GetTag() == Tag::peterjr)
						object->GetComponent<PeterPepperComponent>()->Hit();
					if(object->GetTag() == Tag::ladder)
					{
						auto laddercomp = object->GetComponent<LadderComponent>();
						if(laddercomp->InRange(GetOwner()))
						{

							if (m_MovementDir.y > 0)
							{
								if (!laddercomp->OnBottom(GetOwner()))
								{
									if (abs(object->GetTransform()->GetWorldPosition().y - GetOwner()->GetTransform()->GetWorldPosition().y) < ladderDist)
									{
										ladderDist = abs(object->GetTransform()->GetWorldPosition().y - GetOwner()->GetTransform()->GetWorldPosition().y);
										ladder = object.get();
									}
								}
								else
								{
									m_DirChanged = false;
									m_MovementDir = m_Direction;
								}
							}
							
							if(m_MovementDir.y < 0)
							{
								if (!laddercomp->OnTop(GetOwner()))
								{
									if (abs(object->GetTransform()->GetWorldPosition().y - GetOwner()->GetTransform()->GetWorldPosition().y) < ladderDist)
									{
										ladderDist = abs(object->GetTransform()->GetWorldPosition().y - GetOwner()->GetTransform()->GetWorldPosition().y);
										ladder = object.get();
									}
								}
								else
								{
									m_DirChanged = false;
									m_MovementDir = m_Direction;
								}
							}
							
						}
					}

					if (object->GetTag() == Tag::platform)
					{
						auto platcomp = object->GetComponent<PlatformComponent>();
						if (platcomp->InRange(GetOwner()))
						{
							if (m_MovementDir.x < 0)
							{
								if (!platcomp->OnLeft(GetOwner()))
								{
									if (abs(object->GetTransform()->GetWorldPosition().x - GetOwner()->GetTransform()->GetWorldPosition().x) < platDist)
									{
										platDist = abs(object->GetTransform()->GetWorldPosition().x - GetOwner()->GetTransform()->GetWorldPosition().x);
										platform = object.get();
									}
								}
								else
								{
									m_DirChanged = true;
									m_MovementDir.x = -m_MovementDir.x;
									m_MovementDir.y = m_Direction.y;
								}
							}
							if (m_MovementDir.x > 0)
							{
								if (!platcomp->OnRight(GetOwner()))
								{
									if (abs(object->GetTransform()->GetWorldPosition().x - GetOwner()->GetTransform()->GetWorldPosition().x) < platDist)
									{
										platDist = abs(object->GetTransform()->GetWorldPosition().x - GetOwner()->GetTransform()->GetWorldPosition().x);
										platform = object.get();
									}
								}
								else
								{
									m_DirChanged = true;
									m_MovementDir.x = -m_MovementDir.x;
									m_MovementDir.y = m_Direction.y;
								}
							}

						}
					}


				}
			}
		}

		if(platform && ladder)
		{
			if(m_DirChanged)
			{
				if (m_MovementDir.y > 0)
				{
					pos.y += m_ClimbSpeed * deltaTime;
					m_State = State::down;
					pos.x = ladder->GetTransform()->GetWorldPosition().x;
					m_Transform->SetLocalPosition(pos);
				}
				else if (m_MovementDir.y < 0)
				{
					pos.y -= m_ClimbSpeed * deltaTime;
					m_State = State::up;
					pos.x = ladder->GetTransform()->GetWorldPosition().x;
					m_Transform->SetLocalPosition(pos);
				}
				else if(ladder->GetComponent<LadderComponent>()->OnTop(GetOwner()))
				{
					pos.y += m_ClimbSpeed * deltaTime;
					m_State = State::down;
					pos.x = ladder->GetTransform()->GetWorldPosition().x;
					m_Transform->SetLocalPosition(pos);
				}
				else
				{
					pos.y -= m_ClimbSpeed * deltaTime;
					m_State = State::up;
					pos.x = ladder->GetTransform()->GetWorldPosition().x;
					m_Transform->SetLocalPosition(pos);
				}
				
			}
			else
			{
				if (abs(m_MovementDir.x) > abs(m_MovementDir.y))
				{
					if (m_MovementDir.x < 0)
					{
						pos.x -= m_Speed * deltaTime;
						m_State = State::left;
						pos.y = platform->GetComponent<PlatformComponent>()->GetFloorY();
						m_Transform->SetLocalPosition(pos);
					}
					if (m_MovementDir.x > 0)
					{
						pos.x += m_Speed * deltaTime;
						m_State = State::right;
						pos.y = platform->GetComponent<PlatformComponent>()->GetFloorY();
						m_Transform->SetLocalPosition(pos);
					}
				}
				else
				{
					if (m_MovementDir.y > 0)
					{
						pos.y += m_ClimbSpeed * deltaTime;
						m_State = State::down;
						pos.x = ladder->GetTransform()->GetWorldPosition().x;
						m_Transform->SetLocalPosition(pos);
					}
					if (m_MovementDir.y < 0)
					{
						pos.y -= m_ClimbSpeed * deltaTime;
						m_State = State::up;
						pos.x = ladder->GetTransform()->GetWorldPosition().x;
						m_Transform->SetLocalPosition(pos);
					}
				}
			}
			
		}
		else if(ladder)
		{
			if (m_MovementDir.y > 0)
			{
				pos.y += m_ClimbSpeed * deltaTime;
				m_State = State::down;
				pos.x = ladder->GetTransform()->GetWorldPosition().x;
				m_Transform->SetLocalPosition(pos);
			}
			if (m_MovementDir.y < 0)
			{
				pos.y -= m_ClimbSpeed * deltaTime;
				m_State = State::up;
				pos.x = ladder->GetTransform()->GetWorldPosition().x;
				m_Transform->SetLocalPosition(pos);
			}
		}
		else if(platform)
		{
			if (m_MovementDir.x < 0)
			{
				pos.x -= m_Speed * deltaTime;
				m_State = State::left;
				pos.y = platform->GetComponent<PlatformComponent>()->GetFloorY();
				m_Transform->SetLocalPosition(pos);
			}
			if (m_MovementDir.x > 0)
			{
				pos.x += m_Speed * deltaTime;
				m_State = State::right;
				pos.y = platform->GetComponent<PlatformComponent>()->GetFloorY();
				m_Transform->SetLocalPosition(pos);
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
	SceneManager::GetInstance().GetActiveScene().Remove(GetOwner());
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
