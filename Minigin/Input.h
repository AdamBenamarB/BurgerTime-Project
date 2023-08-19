#pragma once
#include <map>
#include <memory>
#include <SDL_scancode.h>
#include <vector>
#include "XBox360Controller.h"
#include "Command.h"

class Input final
{
public:
	enum class KeyState
	{
		OnPressed,
		OnReleased,
		Held
	};

	Input() = default;
	~Input() = default;

	void AddController(int index);

	void CheckControllers();

	using ControllerKey = std::tuple<unsigned, dae::XBox360Controller::ControllerButton, KeyState>;
	using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<dae::Command>>;
	using KeyCommand = std::pair<SDL_Scancode, KeyState>;
	using KeyboardCommandsMap = std::map<KeyCommand, std::unique_ptr<dae::Command>>;
	KeyboardCommandsMap m_keyCommands{};
	ControllerCommandsMap m_consoleCommands{};
	std::vector<std::unique_ptr<dae::XBox360Controller>> m_controllers{};
};