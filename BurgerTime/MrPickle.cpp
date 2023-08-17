#include "MrPickle.h"

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

dae::MrPickle::MrPickle(dae::Scene& scene, Vec2 loc, GameObject* peter)
{
	Initialize(scene, loc, peter);
}

void dae::MrPickle::Initialize(dae::Scene& scene, Vec2 loc, GameObject* peter)
{
	auto go = std::make_shared<dae::GameObject>();

	auto col = go->AddComponent<CollisionComponent>();
	col->SetSize(32, 32);

	auto enemycomp = go->AddComponent<EnemyComponent>();
	enemycomp->SetPeter(peter);

	auto rc = go->AddComponent<dae::AnimatedRenderComponent>();
	rc->SetDimensions(m_Height, m_Width);
	rc->SetSpriteDimensions(16, 16);
	enemycomp->InitAnimation(rc, "\\Sprites\\Enemies\\pickle.png");

	go->SetTag(Tag::pickle);

	go->GetTransform()->SetLocalPosition(loc.x, loc.y, 0);
	scene.Add(go);
}
