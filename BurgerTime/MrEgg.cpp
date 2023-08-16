#include "MrEgg.h"

#include "AnimatedRenderComponent.h"
#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Input.h"
#include "InputManager.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include "Tags.h"

dae::MrEgg::MrEgg(dae::Scene& scene, Vec2 loc, GameObject* peter)
{
	Initialize(scene, loc, peter);
}

void dae::MrEgg::Initialize(dae::Scene& scene, Vec2 loc, GameObject* peter)
{
	auto go = std::make_shared<dae::GameObject>();
	auto enemycomp = go->AddComponent<EnemyComponent>();
	enemycomp->SetPeter(peter);

	auto rc = go->AddComponent<dae::AnimatedRenderComponent>();
	rc->SetDimensions(m_Height, m_Width);
	rc->SetSpriteDimensions(16, 16);
	enemycomp->InitAnimation(rc, "\\Sprites\\Enemies\\egg.png");

	auto col = go->AddComponent<CollisionComponent>();
	col->SetSize(20, 32.5f);
	col->SetOffset(6, 0);

	go->SetTag(Tag::egg);

	go->GetTransform()->SetLocalPosition(loc.x , loc.y, 0);
	scene.Add(go);
}
