#include "LadderComponent.h"

#include "SceneManager.h"
#include "Scene.h"
#include "Tags.h"

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
				if (otherpos.y > pos.y)
					m_IsBottom = false;
				if (otherpos.y < pos.y)
					m_IsTop = false;
			}
		}
	}
	m_CheckedPos = true;
}

bool dae::LadderComponent::OnBottom(GameObject* go)
{
	if (IsBottom())
		return GetOwner()->GetTransform()->GetWorldPosition().y - go->GetTransform()->GetWorldPosition().y < 2;
	return go->GetTransform()->GetWorldPosition().y - GetOwner()->GetTransform()->GetWorldPosition().y > 31;
}

bool dae::LadderComponent::OnTop(GameObject* go)
{
	if(IsTop())
		return go->GetTransform()->GetWorldPosition().y - GetOwner()->GetTransform()->GetWorldPosition().y < -31;
	return false;
}
