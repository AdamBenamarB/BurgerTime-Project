#pragma once
#include <iostream>

#include "FPS.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "PeterPepperComponent.h"
#include "../BurgerTime/MenuComponent.h"
#include "../BurgerTime/PepperComponent.h"
#include "../BurgerTime/PlayerDogComponent.h"

namespace dae
{
	class MenuComponent;

	class Command
	{
	public:
		explicit Command(std::shared_ptr<GameObject> obj) :object{ obj } {}
		virtual ~Command() = default;
		virtual void Execute() = 0;
	protected:
		std::shared_ptr<GameObject>  GetGameObject() { return object; }
	private:
		std::shared_ptr<GameObject>  object;
	};

#pragma region //PETER
	class Idle : public Command
	{
	public:
		Idle(std::shared_ptr<GameObject> obj) : Command(obj) {}
		void Execute() override { GetGameObject()->GetComponent<PeterPepperComponent>()->SetState(PeterPepperComponent::State::idle); }
	};

	class MoveLeft : public Command
	{
	public:
		MoveLeft(std::shared_ptr<GameObject> obj) : Command(obj) {}
		void Execute() override { GetGameObject()->GetComponent<PeterPepperComponent>()->SetState(PeterPepperComponent::State::left); }
	};

	class MoveRight : public Command
	{
	public:
		MoveRight(std::shared_ptr<GameObject> obj) : Command(obj) {}
		void Execute() override { GetGameObject()->GetComponent<PeterPepperComponent>()->SetState(PeterPepperComponent::State::right); }
	};

	class MoveUp : public Command
	{
	public:
		MoveUp(std::shared_ptr<GameObject> obj) : Command(obj) {}
		void Execute() override { GetGameObject()->GetComponent<PeterPepperComponent>()->SetState(PeterPepperComponent::State::up); }
	};

	class MoveDown : public Command
	{
	public:
		MoveDown(std::shared_ptr<GameObject> obj) : Command(obj) {}
		void Execute() override { GetGameObject()->GetComponent<PeterPepperComponent>()->SetState(PeterPepperComponent::State::down); }
	};

	class Pepper : public Command
	{
	public:
		Pepper(std::shared_ptr<GameObject> obj) : Command(obj) {}
		void Execute() override { GetGameObject()->GetComponent<PepperComponent>()->Activate(); }
	};
#pragma endregion 
#pragma region //MENU
	class MenuNext : public Command
	{
	public:
		MenuNext(std::shared_ptr<GameObject> obj) : Command(obj) {}
		void Execute() override { GetGameObject()->GetComponent<MenuComponent>()->NextSelection(); }
	};

	class MenuPrevious : public Command
	{
	public:
		MenuPrevious(std::shared_ptr<GameObject> obj) : Command(obj) {}
		void Execute() override { GetGameObject()->GetComponent<MenuComponent>()->PreviousSelection(); }
	};

	class MenuStart : public Command
	{
	public:
		MenuStart(std::shared_ptr<GameObject> obj) : Command(obj) {}
		void Execute() override { GetGameObject()->GetComponent<MenuComponent>()->Start(); }
	};
#pragma endregion

	class DogIdle : public Command
	{
	public:
		DogIdle(std::shared_ptr<GameObject> obj) : Command(obj) {}
		void Execute() override { GetGameObject()->GetComponent<PlayerDogComponent>()->SetState(PlayerDogComponent::State::idle); }
	};

	class DogMoveLeft : public Command
	{
	public:
		DogMoveLeft(std::shared_ptr<GameObject> obj) : Command(obj) {}
		void Execute() override { GetGameObject()->GetComponent<PlayerDogComponent>()->SetState(PlayerDogComponent::State::left); }
	};

	class DogMoveRight : public Command
	{
	public:
		DogMoveRight(std::shared_ptr<GameObject> obj) : Command(obj) {}
		void Execute() override { GetGameObject()->GetComponent<PlayerDogComponent>()->SetState(PlayerDogComponent::State::right); }
	};

	class DogMoveUp : public Command
	{
	public:
		DogMoveUp(std::shared_ptr<GameObject> obj) : Command(obj) {}
		void Execute() override { GetGameObject()->GetComponent<PlayerDogComponent>()->SetState(PlayerDogComponent::State::up); }
	};

	class DogMoveDown : public Command
	{
	public:
		DogMoveDown(std::shared_ptr<GameObject> obj) : Command(obj) {}
		void Execute() override { GetGameObject()->GetComponent<PlayerDogComponent>()->SetState(PlayerDogComponent::State::down); }
	};
}
