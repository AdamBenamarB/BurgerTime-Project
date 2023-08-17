#include "Transform.h"

#include <iostream>

#include "GameObject.h"
#include "..\BurgerTime\EnemyComponent.h"

dae::Transform::Transform(GameObject* obj)
	:Component(obj){}

const glm::vec3& dae::Transform::GetLocalPosition() const
{
	return m_LocalPosition;
}

const glm::vec3& dae::Transform::GetWorldPosition()
{

	if (m_IsDirty)
	{
		UpdateWorldPosition();
	}

	return m_WorldPosition;
}


void dae::Transform::SetLocalPosition(const float x, const float y, const float z)
{

	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;

	SetDirty();
}

void dae::Transform::SetLocalPosition(const glm::vec3& pos)
{
	SetLocalPosition(pos.x, pos.y, pos.z);
}

void dae::Transform::UpdateWorldPosition()
{
	GameObject* owner = GetOwner();

	if (owner->GetParent() == nullptr)
	{
		m_WorldPosition = m_LocalPosition;
	}
	else
	{
		auto parentPos = owner->GetParent()->GetTransform()->GetWorldPosition();
		m_WorldPosition = parentPos + m_LocalPosition;
		if(m_WorldPosition.x > 600)
		{
			m_WorldPosition = m_WorldPosition;
		}
		
	}
	m_IsDirty = false;
}

void dae::Transform::SetDirty()
{
	m_IsDirty = true;
	auto childrenVec = GetOwner()->GetChildren();
	for(auto child : childrenVec)
	{
		child->GetTransform()->SetDirty();
	}
}
