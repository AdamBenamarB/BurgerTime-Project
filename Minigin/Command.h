#pragma once
#include <iostream>

#include "FPS.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "PeterPepperComponent.h"

namespace dae
{
	
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

	class FPSTest : public Command
	{
	public:
		FPSTest(std::shared_ptr<GameObject> obj) :Command(obj) {}
		void Execute() override { GetGameObject()->GetComponent<FPS>()->Test(); }
	};
	
	class RemoveHealth : public Command
	{
	public:
		RemoveHealth(std::shared_ptr<GameObject> obj) : Command(obj){}
		void Execute() override { GetGameObject()->GetComponent<HealthComponent>()->Hit(); }
	};

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


}
