#include "EnemySpawnComponent.h"

#include <iostream>

#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "GameObject.h"
#include "MrEgg.h"
#include "MrHotDog.h"
#include "MrPickle.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Tags.h"

dae::EnemySpawnComponent::EnemySpawnComponent(GameObject* owner)
	:Component(owner)
{
	m_ELapsedTime = m_TimePerSpawn;
}

void dae::EnemySpawnComponent::Update(float deltaTime)
{
	m_ELapsedTime += deltaTime;
	if(m_ELapsedTime>=m_TimePerSpawn)
	{
		m_ELapsedTime = 0;
		int random = rand() % 4;

		auto& scene = SceneManager::GetInstance().GetActiveScene();
		if(!m_Peter)
		{
			for(auto& obj:scene.GetObjects())
			{
				if (obj->GetTag() == Tag::peter)
					m_Peter = obj.get();
			}
			
		}

		auto& pos = GetOwner()->GetTransform()->GetWorldPosition();
			

		if(random <2)
		{
			MrHotDog{ scene,{pos.x,pos.y},m_Peter };
		}
		else if (random == 2)
		{
			MrEgg{ scene,{pos.x,pos.y},m_Peter };
		}
		else if (random == 3)
		{
			MrPickle{ scene,{pos.x,pos.y},m_Peter };
		}
	}

}
