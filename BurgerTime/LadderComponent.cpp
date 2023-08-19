#include "LadderComponent.h"

#include <iostream>

#include "SceneManager.h"
#include "Scene.h"
#include "Tags.h"
#include "GameObject.h"

bool dae::LadderComponent::IsBottom()
{
	if (!m_CheckedPos)
		CheckPos();
	return m_IsBottom;
}

bool dae::LadderComponent::IsTop()
{
	if (!m_CheckedPos)
		CheckPos();
	return m_IsTop;
}

void dae::LadderComponent::CheckPos()
{
	auto pos = GetOwner()->GetTransform()->GetWorldPosition();
	for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
	{
		if (object.get() != GetOwner() && object->GetTag() == Tag::ladder)
		{
			auto otherpos = object->GetTransform()->GetWorldPosition();
			if (otherpos.x == pos.x)
			{
				if (otherpos.y == pos.y + 64)
					m_IsBottom = false;
				if (otherpos.y == pos.y - 64)
					m_IsTop = false;
			}
		}
	}

	m_CheckedPos = true;
}

bool dae::LadderComponent::OnBottom(GameObject* go)
{
	if (IsBottom())
		return GetOwner()->GetTransform()->GetWorldPosition().y + 32 - go->GetTransform()->GetWorldPosition().y < 2;
	return go->GetTransform()->GetWorldPosition().y - GetOwner()->GetTransform()->GetWorldPosition().y > 63;
}

bool dae::LadderComponent::OnTop(GameObject* go)
{
	if(IsTop())
		return go->GetTransform()->GetWorldPosition().y - GetOwner()->GetTransform()->GetWorldPosition().y < -63;
	return false;
}

bool dae::LadderComponent::InRange(GameObject* go)
{
	return abs(go->GetTransform()->GetWorldPosition().x - GetOwner()->GetTransform()->GetWorldPosition().x) < m_ClimbRange;
}
