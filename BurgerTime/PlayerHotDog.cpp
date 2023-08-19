#include "PlayerHotDog.h"

#include "AnimatedRenderComponent.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Input.h"
#include "InputManager.h"
#include "PlayerDogComponent.h"
#include "Scene.h"
#include "Tags.h"

dae::PlayerHotDog::PlayerHotDog(dae::Scene& scene, Vec2 loc, bool keyboardControls)
{
	Initialize(scene, loc, keyboardControls);
}

void dae::PlayerHotDog::Initialize(dae::Scene& scene, Vec2 loc, bool keyboardControls)
{
	auto go = std::make_shared<dae::GameObject>();
	m_PlayerDog = go.get();
	go->SetTag(Tag::playerdog);

	go->AddComponent<dae::CollisionComponent>()->SetSize(32, 32);

	auto rc = go->AddComponent<dae::AnimatedRenderComponent>();
	rc->SetTexture("\\Sprites\\Enemies\\dog.png");
	rc->SetDimensions(m_Height, m_Width);
	rc->SetSpriteDimensions(16, 16);

	go->AddComponent<dae::PlayerDogComponent>()->InitAnimation(rc);
	go->GetTransform()->SetLocalPosition(loc.x, loc.y, 0);

	scene.Add(go);

	if (keyboardControls)
	{

		auto keyBoardKey = Input::KeyCommand(SDL_SCANCODE_LEFT, Input::KeyState::OnPressed);
		auto controllerkey = Input::ControllerKey({ 1, dae::XBox360Controller::ControllerButton::DpadLeft,Input::KeyState::OnPressed });
		auto command = std::make_shared<dae::DogMoveLeft>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, command);

		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_LEFT, Input::KeyState::OnReleased);
		controllerkey = Input::ControllerKey({ 1, dae::XBox360Controller::ControllerButton::DpadLeft,Input::KeyState::OnReleased });
		auto idlecommand = std::make_shared<dae::DogIdle>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, idlecommand);

		//RIGHT

		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_RIGHT, Input::KeyState::OnPressed);
		controllerkey = Input::ControllerKey({ 1, dae::XBox360Controller::ControllerButton::DpadRight,Input::KeyState::OnPressed });
		auto command2 = std::make_shared<dae::DogMoveRight>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command2);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, command2);

		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_RIGHT, Input::KeyState::OnReleased);
		controllerkey = Input::ControllerKey({ 1, dae::XBox360Controller::ControllerButton::DpadRight,Input::KeyState::OnReleased });
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, idlecommand);

		//UP
		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_UP, Input::KeyState::OnPressed);
		controllerkey = Input::ControllerKey({ 1, dae::XBox360Controller::ControllerButton::DpadUp,Input::KeyState::OnPressed });
		auto command3 = std::make_shared<dae::DogMoveUp>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command3);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, command3);

		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_UP, Input::KeyState::OnReleased);
		controllerkey = Input::ControllerKey({ 1, dae::XBox360Controller::ControllerButton::DpadUp,Input::KeyState::OnReleased });
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, idlecommand);

		//DOWN
		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_DOWN, Input::KeyState::OnPressed);
		controllerkey = Input::ControllerKey({ 1, dae::XBox360Controller::ControllerButton::DpadDown,Input::KeyState::OnPressed });
		auto command4 = std::make_shared<dae::DogMoveDown>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command4);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, command4);

		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_DOWN, Input::KeyState::OnReleased);
		controllerkey = Input::ControllerKey({ 1, dae::XBox360Controller::ControllerButton::DpadDown,Input::KeyState::OnReleased });
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, idlecommand);
		
	}
	else
	{
		auto controllerkey = Input::ControllerKey({ 1, dae::XBox360Controller::ControllerButton::DpadLeft,Input::KeyState::OnPressed });
		auto command = std::make_shared<dae::DogMoveLeft>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command);

		controllerkey = Input::ControllerKey({ 1, dae::XBox360Controller::ControllerButton::DpadLeft,Input::KeyState::OnReleased });
		auto idlecommand = std::make_shared<dae::DogIdle>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);

		//RIGHT
		controllerkey = Input::ControllerKey({ 1, dae::XBox360Controller::ControllerButton::DpadRight,Input::KeyState::OnPressed });
		auto command2 = std::make_shared<dae::DogMoveRight>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command2);

		controllerkey = Input::ControllerKey({ 1, dae::XBox360Controller::ControllerButton::DpadRight,Input::KeyState::OnReleased });
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);

		//UP
		controllerkey = Input::ControllerKey({ 1, dae::XBox360Controller::ControllerButton::DpadUp,Input::KeyState::OnPressed });
		auto command3 = std::make_shared<dae::DogMoveUp>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command3);

		controllerkey = Input::ControllerKey({ 1, dae::XBox360Controller::ControllerButton::DpadUp,Input::KeyState::OnReleased });
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);

		//DOWN
		controllerkey = Input::ControllerKey({ 1, dae::XBox360Controller::ControllerButton::DpadDown,Input::KeyState::OnPressed });
		auto command4 = std::make_shared<dae::DogMoveDown>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command4);

		controllerkey = Input::ControllerKey({ 1, dae::XBox360Controller::ControllerButton::DpadDown,Input::KeyState::OnReleased });
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);
		
	}


}

dae::GameObject* dae::PlayerHotDog::GetGameObject()
{
	return m_PlayerDog;
}

