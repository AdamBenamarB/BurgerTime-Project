#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "CollisionComponent.h"
#include "FPS.h"
#include "GameObject.h"
#include "HealthDisplayComponent.h"
#include "Input.h"
#include "InputManager.h"
#include "PeterPepperComponent.h"
#include "PlatformComponent.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Tags.h"
#include "TextComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	/*auto go = std::make_shared<dae::GameObject>();
	auto rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("logo.tga");
	go->GetTransform()->SetLocalPosition(216, 180,0);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	auto text = go->AddComponent<dae::TextComponent>();
	text->SetText("Programming 4 Assignment");
	text->SetFont(font);
	go->GetTransform()->SetLocalPosition(80, 20,0);
	scene.Add(go);

	auto gg = go;

	go = std::make_shared<dae::GameObject>();
	text = go->AddComponent<dae::TextComponent>();
	text->SetFont(font);
	go->AddComponent<dae::FPS>();
	go->GetTransform()->SetLocalPosition(10, 10, 0);
	scene.Add(go);

	gg->SetParent(go.get());

	auto controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::ButtonA,Input::KeyState::OnPressed });
	auto command = std::make_unique<dae::FPSTest>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command));

	auto pp = std::make_shared<dae::GameObject>();
	pp->AddComponent<dae::HealthComponent>();
	scene.Add(pp);

	controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::ButtonB,Input::KeyState::OnPressed });
	auto command2 = std::make_unique<dae::RemoveHealth>(pp);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command2));

	go = std::make_shared<dae::GameObject>();
	auto hdisp = go->AddComponent<dae::HealthDisplayComponent>();
	go->GetTransform()->SetLocalPosition(80, 20, 0);
	hdisp->SetActorToDisplay(pp.get());
	pp->GetComponent<dae::HealthComponent>()->AddObserver(hdisp);
	scene.Add(go);*/

	//Ladder
	auto ladder = std::make_shared<dae::GameObject>();
	auto rc = ladder->AddComponent<dae::RenderComponent>();
	rc->SetDimensions(16, 16);
	rc->SetTexture("\\Sprites\\World\\ladder.png");
	ladder->AddComponent<dae::CollisionComponent>()->SetSize(16, 16);
	ladder->GetTransform()->SetLocalPosition(150, 10, 0);
	ladder->SetTag(Tag::ladder);

	scene.Add(ladder);

	ladder = std::make_shared<dae::GameObject>();
	rc = ladder->AddComponent<dae::RenderComponent>();
	rc->SetDimensions(16, 16);
	rc->SetTexture("\\Sprites\\World\\ladder.png");
	ladder->AddComponent<dae::CollisionComponent>()->SetSize(16, 16);
	ladder->GetTransform()->SetLocalPosition(150, 26, 0);
	ladder->SetTag(Tag::ladder);

	scene.Add(ladder);

	auto peterpepper = std::make_shared<dae::GameObject>();
	peterpepper->AddComponent<dae::HealthComponent>();
	peterpepper->AddComponent<dae::CollisionComponent>()->SetSize(16, 16);
	rc = peterpepper->AddComponent<dae::RenderComponent>();
	rc->SetTexture("\\Sprites\\PeterPepper\\peter.png");
	peterpepper->AddComponent<dae::PeterPepperComponent>();
	peterpepper->GetTransform()->SetLocalPosition(10, 10, 0);

	for (int i{}; i < 10; ++i)
	{
		auto platform = std::make_shared<dae::GameObject>();
		rc = platform->AddComponent<dae::RenderComponent>();
		rc->SetDimensions(16, 16);
		rc->SetTexture("\\Sprites\\World\\platform.png");
		platform->AddComponent<dae::CollisionComponent>()->SetSize(16, 16);
		platform->AddComponent<dae::PlatformComponent>();
		platform->GetTransform()->SetLocalPosition(10 + float(i * 16), 10, 0);
		platform->SetTag(Tag::platform);

		scene.Add(platform);
	}

	//LEFT
	auto controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::DpadLeft,Input::KeyState::OnPressed });
	auto command = std::make_unique<dae::MoveLeft>(peterpepper);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command));

	controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::DpadLeft,Input::KeyState::OnReleased });
	auto command2 = std::make_unique<dae::Idle>(peterpepper);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command2));

	//RIGHT
	controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::DpadRight,Input::KeyState::OnPressed });
	auto command3 = std::make_unique<dae::MoveRight>(peterpepper);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command3));

	controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::DpadRight,Input::KeyState::OnReleased });
	auto command4 = std::make_unique<dae::Idle>(peterpepper);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command4));

	//UP
	controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::DpadUp,Input::KeyState::OnPressed });
	auto command5 = std::make_unique<dae::MoveUp>(peterpepper);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command5));

	controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::DpadUp,Input::KeyState::OnReleased });
	auto command6 = std::make_unique<dae::Idle>(peterpepper);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command6));

	//DOWN
	controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::DpadDown,Input::KeyState::OnPressed });
	auto command7 = std::make_unique<dae::MoveDown>(peterpepper);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command7));

	controllerkey = Input::ControllerKey({ 0, dae::XBox360Controller::ControllerButton::DpadDown,Input::KeyState::OnReleased });
	auto command8 = std::make_unique<dae::Idle>(peterpepper);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command8));

	scene.Add(peterpepper);

	/*auto peter2 = std::make_shared<dae::GameObject>();
	rc = peter2->AddComponent<dae::RenderComponent>();
	peter2->AddComponent<dae::CollisionComponent>()->SetSize(16, 16);
	rc->SetTexture("\\Sprites\\PeterPepper\\peter.png");
	peter2->AddComponent<dae::PeterPepperComponent>();
	peter2->GetTransform()->SetLocalPosition(100, 10, 0);

	scene.Add(peter2);*/



}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}