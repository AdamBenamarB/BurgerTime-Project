#include "InputManager.h"
#include "Command.h"
#include <iostream>
#include <SDL_events.h>


dae::InputManager::InputManager()
{

}


void dae::InputManager::Update(float deltaTime)
{
	m_ElapsedControllerCheck += deltaTime;
	if (m_ElapsedControllerCheck >= m_ControllerCheckInterval)
	{
		m_ElapsedControllerCheck = 0.f;
		//m_input.CheckControllers();
	}
	for (auto& controller : m_input.m_controllers)
	{
		controller->Update();
	}
}

bool dae::InputManager::HandleInput()
{
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

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}

	return true;
}

bool dae::InputManager::IsPressed(XBox360Controller::ControllerButton button, int controllerIdx)
{
	return m_input.m_controllers.at(controllerIdx)->IsPressed(button);
}


void dae::InputManager::AddCommand(Input::ControllerKey controllerKey, std::unique_ptr<Command> command)
{
	m_input.m_consoleCommands.insert({ controllerKey, std::move(command) });
}

void dae::InputManager::RemoveCommand(Input::ControllerKey controllerKey)
{
	m_input.m_consoleCommands.erase(controllerKey);
}

void dae::InputManager::RemoveCommands()
{
	m_input.m_consoleCommands.clear();
}