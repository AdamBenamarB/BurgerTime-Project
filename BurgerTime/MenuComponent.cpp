#include "MenuComponent.h"

#include <iostream>
#include <thread>

#include "GameInstance.h"
#include "NextScreen.h"
#include "TextComponent.h"

void dae::MenuComponent::SetTextComps(const std::vector<TextComponent*>& textComps)
{
	m_SinglePlayer = textComps.at(0);
	m_Coop = textComps.at(1);
	m_Versus = textComps.at(2);
	m_Name = textComps.at(3);
	
}

void dae::MenuComponent::NextSelection()
{
	switch(m_Selection)
	{
	case Selection::singleplayer:
		m_Selection = Selection::coop;
		m_SinglePlayer->SetColor(1, 1, 1, 1);
		m_Coop->SetColor(1, 0, 0, 1);
		break;
	case Selection::coop:
		m_Selection = Selection::versus;
		m_Coop->SetColor(1, 1, 1, 1);
		m_Versus->SetColor(1, 0, 0, 1);
		break;
	case Selection::versus:
		m_Selection = Selection::singleplayer;
		m_Versus->SetColor(1, 1, 1, 1);
		m_SinglePlayer->SetColor(1, 0, 0, 1);
		break;
	}
}

void dae::MenuComponent::PreviousSelection()
{
	switch (m_Selection)
	{
	case Selection::singleplayer:
		m_Selection = Selection::versus;
		m_SinglePlayer->SetColor(1, 1, 1, 1);
		m_Versus->SetColor(1, 0, 0, 1);
		break;
	case Selection::coop:
		m_Selection = Selection::singleplayer;
		m_Coop->SetColor(1, 1, 1, 1);
		m_SinglePlayer->SetColor(1, 0, 0, 1);
		break;
	case Selection::versus:
		m_Selection = Selection::coop;
		m_Versus->SetColor(1, 1, 1, 1);
		m_Coop->SetColor(1, 0, 0, 1);
		break;
	}
}


void dae::MenuComponent::Start()
{
	m_Name->SetText("enter name");
	std::cin >> m_NameStr;
	GameInstance::GetInstance().SetName(m_NameStr);

	if (!m_Started)
	{
		switch (m_Selection)
		{
		case Selection::singleplayer:
			GameInstance::GetInstance().SetGameMode(GameMode::singleplayer);
			break;
		case Selection::coop:
			GameInstance::GetInstance().SetGameMode(GameMode::coop);
			break;
		case Selection::versus:
			GameInstance::GetInstance().SetGameMode(GameMode::versus);
			break;
		}
		m_Started = true;
		NextScreen{};
	}
		
}
