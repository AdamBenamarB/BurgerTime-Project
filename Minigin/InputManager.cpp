#include "InputManager.h"
#include "Command.h"
#include <iostream>
#include <SDL_events.h>

#include "ServiceLocator.h"
#include "../BurgerTime/GameInstance.h"

dae::InputManager::InputManager()
{

}


//void dae::InputManager::Update(float deltaTime)
//{
//	m_ElapsedControllerCheck += deltaTime;
//	if (m_ElapsedControllerCheck >= m_ControllerCheckInterval)
//	{
//		m_ElapsedControllerCheck = 0.f;
//	}
//	
//}

bool dae::InputManager::HandleInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {

		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			for (const auto& command : m_input.m_keyCommands)
			{
				if (command.first.second == Input::KeyState::OnPressed)
				{
					if (e.key.keysym.scancode == command.first.first)
						command.second.get()->Execute();
				}
			}
		}
		if (e.type == SDL_KEYUP)
		{
			for (const auto& command : m_input.m_keyCommands)
			{
				if (command.first.second == Input::KeyState::OnReleased)
				{
					if (e.key.keysym.scancode == command.first.first)
						command.second.get()->Execute();
				}
			}

			if(e.key.keysym.scancode == SDL_SCANCODE_M)
			{
				ServiceLocator::GetSoundSystem().Mute();
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_F1)
			{
				GameInstance::GetInstance().LoadNextLevel();
			}
		}
	}


	for (auto& controller : m_input.m_controllers)
	{
		controller->Update();
	}
	auto it = m_input.m_consoleCommands.begin();
	while (it != m_input.m_consoleCommands.end())
	{

		if (std::get<2>(it->first) == Input::KeyState::OnPressed)
		{
			if (m_input.m_controllers.at(std::get<0>(it->first))->IsDown(std::get<1>(it->first)))
			{
				it->second->Execute();
			}
		}
		if (std::get<2>(it->first) == Input::KeyState::OnReleased)
		{
			if (m_input.m_controllers.at(std::get<0>(it->first))->IsUp(std::get<1>(it->first)))
			{
				it->second->Execute();
			}
		}
		if (std::get<2>(it->first) == Input::KeyState::Held)
		{
			if (m_input.m_controllers.at(std::get<0>(it->first))->IsPressed(std::get<1>(it->first)))
			{
				it->second->Execute();
			}
		}
		++it;
	}

	return true;
}

bool dae::InputManager::IsPressed(XBox360Controller::ControllerButton button, int controllerIdx)
{
	return m_input.m_controllers.at(controllerIdx)->IsPressed(button);
}


void dae::InputManager::AddCommand(Input::ControllerKey controllerKey, std::shared_ptr<Command> command)
{
	m_input.m_consoleCommands.insert({ controllerKey, command });
}

void dae::InputManager::AddCommand(Input::KeyCommand keyCommand, std::shared_ptr<Command> command)
{
	m_input.m_keyCommands.insert({ keyCommand, command});
}

void dae::InputManager::RemoveCommand(Input::ControllerKey controllerKey)
{
	m_input.m_consoleCommands.erase(controllerKey);
}

void dae::InputManager::RemoveCommands()
{
	m_input.m_consoleCommands.clear();
}