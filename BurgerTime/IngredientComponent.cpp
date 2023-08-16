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
	if(m_Platform)
	std::cout << int(m_State) << std::endl;
	switch(m_State)
	{
	case State::idle:
		{
			for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
			{
				for (int i{}; i < m_Collisions.size(); ++i)
				{
					if (m_Collisions[i]->IsOverlapping(obj.get()))
					{
						if (obj->GetTag() == Tag::peter)
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
					}
				}
			}

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
			}
			else
				m_Enemies.clear();
			break;
		}
	case State::falling:
		{
		for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			
				if (m_Collisions[0]->IsOverlapping(obj.get()))
				{
					if (obj.get() == m_Platform)
						break;
					if (obj->GetTag() == Tag::platform && obj.get() != m_Platform)
					{
						if (obj->GetComponent<PlatformComponent>()->OnBottom(GetOwner()))
						{
							m_State = State::idle;
							m_Platform = obj.get();
							for (int i{}; i < 4; ++i)
							{
								m_DropStates[i] = false;
								m_Sprites[i]->SetOffsetY(0);
							}
							for(auto enemy: m_Enemies)
							{
								enemy->GetComponent<EnemyComponent>()->SetState(EnemyComponent::State::left);
								enemy->SetParent(nullptr);
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
						m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(50);
						ServiceLocator::GetSoundSystem().Play(m_Bounce, 100);
					}
				}
			
		}
		}
	}


	/*if (m_State == State::idle)
	{
		m_Next = false;
		m_Enemies.clear();
		bool onPlatform = false;
		for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			int amtDropped{};
			for (int i{}; i < 4; ++i)
			{
				if (m_DropStates[i] == true)
					++amtDropped;
			}

			for (int i{}; i < m_Collisions.size(); ++i)
			{
				if (m_Collisions[i]->IsOverlapping(obj.get()))
					if (obj->GetTag() == Tag::peter)
					{
						m_Peter = obj.get();
						m_DropStates[i] = true;
						m_Sprites[i]->SetOffsetY(5);
					}
					else if (obj->GetComponent<EnemyComponent>())
					{
						bool exists = false;
						for (auto& enemy : m_Enemies)
							if (enemy == obj.get())
								exists = true;
						if (!exists)
							m_Enemies.push_back(obj.get());
					}
					else if (i == 1)
					{
						if (obj->GetTag() == Tag::platform)
						{
							onPlatform = true;
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
		}
		if (!onPlatform)
			m_State = State::falling;

		for (int i{}; i < 4; ++i)
		{
			if (m_DropStates[i] == false)
				return;
		}
		SetState(State::falling);
		m_CollidedIngredient = nullptr;
		for (int i{}; i < 4; ++i)
		{
			m_DropStates[i] = false;
			m_Sprites[i]->SetOffsetY(0);
		}
		m_LevelsToFall = (int)m_Enemies.size();
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
		else if (m_LevelsToFall == 6)
			m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(1600);
		for (auto& enemy : m_Enemies)
		{
			enemy->GetComponent<EnemyComponent>()->SetState(EnemyComponent::State::falling);
		}
	}
	else if (m_State == State::falling)
	{
		for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{

			if (m_Collisions[1]->IsOverlapping(obj.get()))
			{
				if (obj.get() != m_Platform)
					if (obj->GetTag() == Tag::platform)
					{
						auto platcomp = obj->GetComponent<PlatformComponent>();
						if (!m_Collisions[1]->IsUnder(obj.get()))
						{
							if (m_LevelsToFall == 0)
							{
								m_Platform = nullptr;
								m_State = State::idle;
								m_CollidedIngredient = nullptr;

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

				if (auto enemy = obj->GetComponent<EnemyComponent>())
				{
					bool enemyOn = false;
					for (auto enemyon : m_Enemies)
						if (enemyon == obj.get())
							enemyOn = true;

					if (!enemyOn)
						enemy->Kill();
				}


				if (auto comp = obj->GetComponent<IngredientComponent>())
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
						m_Next = true;
					}
				}


				if (obj->GetTag() == Tag::plate)
				{
					m_State = State::plated;
					m_Enemies.clear();
					m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(50);
					ServiceLocator::GetSoundSystem().Play(m_Bounce, 100);
				}

			}
		}

	}*/
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
