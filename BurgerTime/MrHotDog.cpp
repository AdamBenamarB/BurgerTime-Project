#include "MrHotDog.h"

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

dae::MrHotDog::MrHotDog(dae::Scene& scene, Vec2 loc, GameObject* peter)
{
	Initialize(scene, loc, peter);
}

void dae::MrHotDog::Initialize(dae::Scene& scene, Vec2 loc, GameObject* peter)
{
	auto go = std::make_shared<dae::GameObject>();
	auto enemycomp = go->AddComponent<EnemyComponent>();
	enemycomp->SetPeter(peter);

	auto rc = go->AddComponent<dae::AnimatedRenderComponent>();
	rc->SetDimensions(m_Height, m_Width);
	rc->SetSpriteDimensions(16, 16);
	enemycomp->InitAnimation(rc, "\\Sprites\\Enemies\\dog.png");

	auto col = go->AddComponent<CollisionComponent>();
	col->SetSize(16, 16);

	go->SetTag(Tag::hotdog);

	go->GetTransform()->SetLocalPosition(loc.x, loc.y, 0);
	scene.Add(go);

	auto controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::Start,Input::KeyState::OnPressed });
	auto command9 = std::make_unique<dae::Kill>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command9));
}
