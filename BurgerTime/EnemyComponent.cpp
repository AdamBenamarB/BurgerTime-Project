#include "EnemyComponent.h"

#include <iostream>

#include "AnimatedRenderComponent.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "LadderComponent.h"
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
	//HandleCollision(deltaTime);
	HandleAnim();
	HandleStun(deltaTime);

	std::cout << "State: " << (int)m_State << '\n' << "Direction x: " << m_Direction.x << " y: " << m_Direction.y << '\n';
	//std::cout << "On Ladder: " << m_OnLadder << '\n';
}

void dae::EnemyComponent::HandleMovement(float deltaTime)
{
	//IF LADDER UNDER LADDER THEN GO DOWN

	glm::vec3 peterPos = m_Peter->GetTransform()->GetWorldPosition();
	glm::vec3 pos = GetOwner()->GetTransform()->GetWorldPosition();

	if(m_OnPlatform)
	m_Direction.y = peterPos.y - pos.y;

	if(m_Direction.x == 0 || m_Direction.y == 0 || m_OnLadder)
	m_Direction.x = peterPos.x - pos.x;

	

	for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
	{
		//if y is bigger than 0 then move x in random direction till ladder,
		//if ladder move on it
		//if y == 0 move x in direction of peter
		if(object->GetComponent<CollisionComponent>())
		{
			if (m_CollisionComp->IsOverlapping(object.get()))
			{
				if (object->GetTag() == Tag::ladder 
					&& abs(m_Transform->GetWorldPosition().x - object->GetTransform()->GetWorldPosition().x) < 2)//check if in range of ladder to not teleport
				{
					if (abs(m_Direction.y) > 1)
					{
						auto pos = m_Transform->GetWorldPosition();
						auto laddercomp = object->GetComponent<LadderComponent>();

						if (m_Direction.y > 0)
						{
							if(!laddercomp->OnBottom(GetOwner()))
							{
								pos.y += m_ClimbSpeed * deltaTime;
								m_State = State::down;
								pos.x = object->GetTransform()->GetWorldPosition().x;
								m_Transform->SetLocalPosition(pos);
								m_OnLadder = true;
								m_OnPlatform = false;
								break;
							}

						}
						if (m_Direction.y < 0 && !laddercomp->OnTop(GetOwner()))//check if ladder can go up or just passes by one
						{
							pos.y -= m_ClimbSpeed * deltaTime;
							m_State = State::up;
							pos.x = object->GetTransform()->GetWorldPosition().x;
							m_Transform->SetLocalPosition(pos);
							m_OnLadder = true;
							m_OnPlatform = false;
							break;
						}

					}
				}
				if (object->GetTag() == Tag::platform)
				{
					auto pos = m_Transform->GetWorldPosition();
					if (m_Direction.x > 1)
					{
						pos.x += m_Speed * deltaTime;
						m_State = State::right;
					}
					if (m_Direction.x < -1)
					{
						pos.x -= m_Speed * deltaTime;
						m_State = State::left;
					}
					pos.y = object->GetTransform()->GetWorldPosition().y;
					m_Transform->SetLocalPosition(pos);
					m_OnLadder = false;
					m_OnPlatform = true;
					break;
				}
			}
		}
		
	}

}

void dae::EnemyComponent::HandleCollision(float deltaTime)
{
	int platforms = 0;
	int ladders = 0;
	GameObject* platform = nullptr;
	GameObject* ladder = nullptr;

	for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
	{
		auto colcomp = object->GetComponent<CollisionComponent>();
		if (colcomp)
		{

			if (m_CollisionComp->IsOverlapping(object.get()))
			{
				if (object->GetTag() == Tag::platform)
				{
					platforms++;
					platform = object.get();
				}
				if (object->GetTag() == Tag::ladder)
				{
					ladders++;
					ladder = object.get();
					
				}
			}
		}
	}
	switch (m_State)
	{
	case State::left:
		if (platforms == 1)
		{
			m_Direction.x = -m_Direction.x;
		}
		break;
	case State::right:
		if (platforms == 1)
		{
			m_Direction.x = -m_Direction.x;
		}
		break;
	case State::up:
		if (ladders == 1)
		{
			
		}
		break;
	case State::down:
		if (ladders == 1)
		{
			if (GetOwner()->GetTransform()->GetWorldPosition().y - ladder->GetTransform()->GetWorldPosition().y > 1)
			{
				auto pos = m_Transform->GetWorldPosition();
				pos.y -= m_ClimbSpeed * deltaTime;
				m_Transform->SetLocalPosition(pos);

				m_OnLadder = false;
				m_OnPlatform = true;
				m_NoLadderDown = true;
			}
		}
		break;
	}
	if(ladders == 0)
	{
		m_NoLadderDown = false;
	}
}

void dae::EnemyComponent::SetState(State state)
{
	m_State = state;
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
