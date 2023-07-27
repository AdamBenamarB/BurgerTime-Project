#include "Input.h"

void Input::AddController(int index)
{
	bool connected = false;
	for (std::unique_ptr<dae::XBox360Controller>& controller : m_controllers)
	{
		if (controller->GetIndex() == index)
		{
			connected = true;
		}
	}
	if (!connected)
	{
		m_controllers.push_back(std::make_unique<dae::XBox360Controller>(index));
	}
}

void Input::CheckControllers()
{
	int* ids = dae::XBox360Controller::GetControllerIds();
	for (int i{}; i < 4; i++)
	{
		if (ids[i] != -1)
		{
			AddController(ids[i]);
		}
	}
}
