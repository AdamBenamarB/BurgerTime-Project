#include "PeterPepper.h"

#include "AnimatedRenderComponent.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Input.h"
#include "InputManager.h"
#include "Scene.h"
#include "Tags.h"

dae::PeterPepper::PeterPepper(dae::Scene& scene, Vec2 loc)
{
	Initialize(scene, loc);
}

void dae::PeterPepper::Initialize(dae::Scene& scene, Vec2 loc)
{
	auto go = std::make_shared<dae::GameObject>();
	m_Peter = go.get();
	go->AddComponent<dae::HealthComponent>();
	go->AddComponent<dae::CollisionComponent>()->SetSize(32, 32);

	/*auto rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("\\Sprites\\PeterPepper\\peter.png");*/

	auto rc = go->AddComponent<dae::AnimatedRenderComponent>();
	rc->SetTexture("\\Sprites\\PeterPepper\\sprites.png");
	rc->SetDimensions(m_Height, m_Width);
	rc->SetSpriteDimensions(16, 16);

	go->AddComponent<dae::PeterPepperComponent>()->InitAnimation(rc);
	go->GetTransform()->SetLocalPosition(loc.x, loc.y, 0);
	scene.Add(go);

	auto controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::DpadLeft,Input::KeyState::OnPressed });
	auto command = std::make_unique<dae::MoveLeft>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command));

	controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::DpadLeft,Input::KeyState::OnReleased });
	auto command2 = std::make_unique<dae::Idle>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command2));

	//RIGHT
	controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::DpadRight,Input::KeyState::OnPressed });
	auto command3 = std::make_unique<dae::MoveRight>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command3));

	controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::DpadRight,Input::KeyState::OnReleased });
	auto command4 = std::make_unique<dae::Idle>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command4));

	//UP
	controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::DpadUp,Input::KeyState::OnPressed });
	auto command5 = std::make_unique<dae::MoveUp>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command5));

	controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::DpadUp,Input::KeyState::OnReleased });
	auto command6 = std::make_unique<dae::Idle>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command6));

	//DOWN
	controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::DpadDown,Input::KeyState::OnPressed });
	auto command7 = std::make_unique<dae::MoveDown>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command7));

	controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::DpadDown,Input::KeyState::OnReleased });
	auto command8 = std::make_unique<dae::Idle>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command8));

	

}

dae::GameObject* dae::PeterPepper::GetGameObject()
{
	return m_Peter;
}

