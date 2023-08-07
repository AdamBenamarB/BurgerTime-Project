#include "PlatformComponent.h"

#include "CollisionComponent.h"
#include "GameObject.h"

dae::PlatformComponent::PlatformComponent(GameObject* owner)
	:Component{ owner }
{

}

Vec2 dae::PlatformComponent::GetFloorPos() const
{
	auto pos = GetOwner()->GetTransform()->GetWorldPosition();
	Vec2 floorPos = { pos.x,pos.y };
	return floorPos;
}
