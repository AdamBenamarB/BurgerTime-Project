#include "CollisionComponent.h"

#include <glm/vec3.hpp>
#include "GameObject.h"

bool dae::CollisionComponent::IsOverlapping(GameObject* other)
{
	if (GetOwner() == other)
		return false;

	if (auto othercol = other->GetComponent<CollisionComponent>())
	{
		auto pos = GetOwner()->GetTransform()->GetWorldPosition();
		pos.x += m_OffsetX;
		pos.y += m_OffsetY;
		glm::vec3 cornerpos{ pos.x + m_Width,pos.y + m_Height,pos.z };

		auto otherpos = other->GetTransform()->GetWorldPosition();
		otherpos.x += othercol->m_OffsetX;
		otherpos.y += othercol->m_OffsetY;
		glm::vec3 othercorner{ otherpos.x + othercol->m_Width,otherpos.y + othercol->m_Height,otherpos.z };

		if (pos.x > othercorner.x || otherpos.x > cornerpos.x)
			return false;

		if (cornerpos.y < otherpos.y || othercorner.y < pos.y)
			return false;

		return true;
	}
	return false;
}


bool dae::CollisionComponent::IsOverlapping(Rect other)
{
	auto pos = GetOwner()->GetTransform()->GetWorldPosition();
	pos.x += m_OffsetX;
	pos.y += m_OffsetY;
	glm::vec3 cornerpos{ pos.x + m_Width,pos.y + m_Height,pos.z };

	glm::vec3 otherpos = { other.x,other.y,0 };
	glm::vec3 othercorner = { other.x + other.width,other.y + other.height,0 };

	if (pos.x > othercorner.x || otherpos.x > cornerpos.x)
		return false;

	if (cornerpos.y < otherpos.y || othercorner.y < pos.y)
		return false;

	return true;
}

void dae::CollisionComponent::SetSize(float width, float height)
{
	m_Width = width;
	m_Height = height;
}
