#include "Platform.h"

#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "PlatformComponent.h"
#include "Scene.h"
#include "Tags.h"

dae::Platform::Platform(dae::Scene& scene, Vec2 loc)
{
	Initialize(scene, loc);
}

void dae::Platform::Initialize(dae::Scene& scene, Vec2 loc)
{
	auto go = std::make_shared<dae::GameObject>();
	auto rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("\\Sprites\\World\\platform.png");
	rc->SetDimensions(32, 32);

	auto col = go->AddComponent<CollisionComponent>();
	col->SetSize(32, 32);

	go->GetTransform()->SetLocalPosition(loc.x, loc.y, 0);

	go->SetTag(Tag::platform);
	scene.Add(go);

}
