#include "PlatformComponent.h"

#include <iostream>

#include "SceneManager.h"
#include "Tags.h"
#include "GameObject.h"
#include "Scene.h"

bool dae::PlatformComponent::OnLeft(GameObject* go)
{
	if (!m_CheckedEdge)
		CheckEdge();
	if (m_IsLeftEdge)
		return go->GetTransform()->GetWorldPosition().x - GetOwner()->GetTransform()->GetWorldPosition().x < 1;
	return false;


}

bool dae::PlatformComponent::OnRight(GameObject* go)
{
	if (!m_CheckedEdge)
		CheckEdge();
	if (m_IsRightEdge)
		return GetOwner()->GetTransform()->GetWorldPosition().x - go->GetTransform()->GetWorldPosition().x < 1;
	return false;
}


void dae::PlatformComponent::CheckEdge()
{
	auto pos = GetOwner()->GetTransform()->GetWorldPosition();
	for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
	{
		if (object.get() != GetOwner() && object->GetTag() == Tag::platform)
		{
			auto otherpos = object->GetTransform()->GetWorldPosition();
			if (otherpos.y == pos.y)
			{
				if (otherpos.x > pos.x)
					m_IsRightEdge = false;
				if (otherpos.x < pos.x)
					m_IsLeftEdge = false;
			}
		}
	}
	m_CheckedEdge = true;
}

bool dae::PlatformComponent::OnBottom(GameObject* go)
{
	return GetOwner()->GetTransform()->GetWorldPosition().y + 23 - go->GetTransform()->GetWorldPosition().y < 1;
}