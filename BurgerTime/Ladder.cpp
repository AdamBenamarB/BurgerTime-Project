#include "Ladder.h"

#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "LadderComponent.h"
#include "Scene.h"
#include "Tags.h"

dae::Ladder::Ladder(dae::Scene& scene, Vec2 loc)
{
	Initialize(scene, loc);
}

void dae::Ladder::Initialize(dae::Scene& scene, Vec2 loc)
{
	auto go = std::make_shared<dae::GameObject>();
	auto rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("\\Sprites\\World\\ladder.png");
	rc->SetDimensions(32, 32);

	auto col = go->AddComponent<CollisionComponent>();
	col->SetSize(32, 32);
	go->GetTransform()->SetLocalPosition(loc.x, loc.y, 0);

	go->AddComponent<LadderComponent>();

	go->SetTag(Tag::ladder);
	scene.Add(go);

}
