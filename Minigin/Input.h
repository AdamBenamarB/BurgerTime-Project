#pragma once
#include <map>
#include <memory>
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
	//using ControllerKey = std::pair<unsigned, dae::XBox360Controller::ControllerButton>;//First value is index of controller to assign to
	using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<dae::Command>>;
	ControllerCommandsMap m_consoleCommands{};
	std::vector<std::unique_ptr<dae::XBox360Controller>> m_controllers{};
};