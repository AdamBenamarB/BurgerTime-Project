#include "IngredientComponent.h"

#include <iostream>

#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "PeterPepperComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "Tags.h"
#include "PlatformComponent.h"
#include "PlayerDogComponent.h"

dae::IngredientComponent::IngredientComponent(GameObject* owner)
	:Component(owner)
{
	Initialize();
}

void dae::IngredientComponent::Update(float deltaTime)
{
	if (!m_Peter)
	{
		for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			if (obj->GetTag() == Tag::peter)
			{
				m_Peter = obj.get();
				break;
			}
		}
	}
	HandleMovement(deltaTime);
	HandleCollision(deltaTime);
}

void dae::IngredientComponent::HandleMovement(float deltaTime)
{
	if (m_State == State::falling)
	{
		auto pos = GetOwner()->GetTransform()->GetWorldPosition();
		pos.y += m_FallSpeed * deltaTime;
		GetOwner()->GetTransform()->SetLocalPosition(pos.x, pos.y, pos.z);
	}

}

void dae::IngredientComponent::HandleCollision(float)// deltaTime)
{
	switch(m_State)
	{
	case State::idle:
		{
		int amtDropped{};
		for (int i{}; i < 4; ++i)
		{
			if (m_DropStates[i] == true)
				++amtDropped;
		}
			for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
			{
				for (int i{}; i < m_Collisions.size(); ++i)
				{
					if (m_Collisions[i]->IsOverlapping(obj.get()))
					{
						if (obj->GetTag() == Tag::peter || obj->GetTag() == Tag::peterjr)
						{
							m_DropStates[i] = true;
							m_Sprites[i]->SetOffsetY(5);

						}
						if (i == 0 && obj.get() != m_Platform && obj->GetTag() == Tag::platform )
						{
							m_Platform = obj.get();
						}
						if(obj->GetComponent<EnemyComponent>())
						{
							if (std::find(m_Enemies.begin(), m_Enemies.end(), obj.get()) == m_Enemies.end())
								m_Enemies.push_back(obj.get());
						}
						if (obj->GetTag() == Tag::playerdog)
						{
							m_PlayerDog = obj.get();
						}
					}
				}
			}

			int after{};
			for (int i{}; i < 4; ++i)
			{
				if (m_DropStates[i] == true)
					++after;
			}
			if (after > amtDropped)
				ServiceLocator::GetSoundSystem().Play(m_Walk, 100);

			bool dropped = true;
			for (int i{}; i < 4; ++i)
			{
				if(m_DropStates[i] == false)
				{
					dropped = false;
					break;
				}
			}

			if (dropped)
			{
				m_State = State::falling;
				auto pos = GetOwner()->GetTransform()->GetWorldPosition();
				pos.y += 8;//under platform
				GetOwner()->GetTransform()->SetLocalPosition(pos.x, pos.y, pos.z);
				for (auto enemy : m_Enemies)
				{
					enemy->GetComponent<EnemyComponent>()->SetState(EnemyComponent::State::falling);
					enemy->SetParent(GetOwner(),true);
				}
				if (m_PlayerDog)
				{
					m_PlayerDog->GetComponent<PlayerDogComponent>()->SetState(PlayerDogComponent::State::falling);
					m_PlayerDog->SetParent(GetOwner(), true);
				}
				m_LevelsToFall = (int)m_Enemies.size();
				if (m_PlayerDog)
					++m_LevelsToFall;
				
				if (m_LevelsToFall == 1)
					m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(500);
				if (m_LevelsToFall == 2)
					m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(1000);
				else if (m_LevelsToFall == 3)
					m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(2000);
				else if (m_LevelsToFall == 4)
					m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(4000);
				else if (m_LevelsToFall == 5)
					m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(8000);
				else if (m_LevelsToFall >= 6)
					m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(16000);
			}
			else
			{
				m_Enemies.clear();
				m_PlayerDog = nullptr;
			}
			break;
		}
	case State::falling:
		{
		for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			for (int i{}; i < m_Collisions.size(); ++i)
			{
				if (m_Collisions[i]->IsOverlapping(obj.get()))
				{
					if (i == 0)
					{
						if (obj.get() == m_Platform)
							break;
						if (obj->GetTag() == Tag::platform && obj.get() != m_Platform)
						{
							if (obj->GetComponent<PlatformComponent>()->OnBottom(GetOwner()))
							{
								if(m_LevelsToFall == 0)
								{
									m_State = State::idle;
									m_Platform = obj.get();
									for (int i{}; i < 4; ++i)
									{
										m_DropStates[i] = false;
										m_Sprites[i]->SetOffsetY(0);
									}
									
									for (auto enemy : m_Enemies)
									{
										enemy->GetComponent<EnemyComponent>()->SetState(EnemyComponent::State::left);
										enemy->SetParent(nullptr);
									}
									if(m_PlayerDog)
									{
										m_PlayerDog->GetComponent<PlayerDogComponent>()->ResetState();
										m_PlayerDog->SetParent(nullptr);
										m_PlayerDog = nullptr;
									}
									m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(50);
									ServiceLocator::GetSoundSystem().Play(m_Bounce, 100);
								}
								else
								{
									m_Platform = obj.get();
									--m_LevelsToFall;
									m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(50);
								}
							}
						}
						else if (auto comp = obj->GetComponent<IngredientComponent>())
						{
							if (comp->m_State == State::plated)
							{
								m_State = State::plated;

								if (GetOwner()->GetTag() == Tag::bun)
									GameInstance::GetInstance().FillPlate();
								ServiceLocator::GetSoundSystem().Play(m_Bounce, 100);
							}
							else {
								m_CollidedIngredient = obj.get();
								comp->SetState(State::falling);
							}
						}
						else if (obj->GetTag() == Tag::plate)
						{
							for (int i{}; i < 4; ++i)
							{
								m_DropStates[i] = false;
								m_Sprites[i]->SetOffsetY(0);
							}
							m_State = State::plated;
							m_Enemies.clear();
							ServiceLocator::GetSoundSystem().Play(m_Bounce, 100);
							m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(50);
						}
					}

					if (auto comp = obj->GetComponent<EnemyComponent>())
					{
						if(comp->GetState() != EnemyComponent::State::falling)
						comp->Kill();

					}
				}

				
			}
				
			
		}
		}
	}
}

void dae::IngredientComponent::SetCollisions(std::vector<CollisionComponent*>& cols)
{
	m_Collisions = cols;
}

void dae::IngredientComponent::SetSprites(std::vector<RenderComponent*>& sprites)
{
	m_Sprites = sprites;
}

void dae::IngredientComponent::SetState(State state)
{
	if (m_State != State::plated)
	{
		m_State = state;
		if (m_State == State::falling)
		{
			for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
			{
				if (m_Collisions[1]->IsOverlapping(obj.get()))
				{
					if (obj->GetTag() == Tag::platform)
					{
						m_Platform = obj.get();
					}
				}
			}
			for (int i{}; i < 4; ++i)
			{
				m_DropStates[i] = false;
				m_Sprites[i]->SetOffsetY(0);
			}
		}
	}
}

void dae::IngredientComponent::Initialize()
{
	m_Walk = dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/ingredientwalk.wav");
	m_Bounce = dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/bounce.wav");
}
