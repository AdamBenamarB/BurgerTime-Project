#include "TransitionComponent.h"

#include <iostream>

#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "MrEgg.h"
#include "Scene.h"
#include "SceneManager.h"

dae::TransitionComponent::TransitionComponent(GameObject* owner)
	:Component(owner)
{
}

void dae::TransitionComponent::Update(float deltaTime)
{
	m_ELapsedTime += deltaTime;
	if (m_ELapsedTime >= m_TransitionTime)
	{
		GameInstance::GetInstance().LoadNextLevel();
	}

}
