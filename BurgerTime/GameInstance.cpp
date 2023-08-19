#include "GameInstance.h"

#include <iostream>

#include "DeathScreen.h"
#include "SceneManager.h"
#include "LevelLoader.h"
#include "NextScreen.h"
#include <algorithm>
#include "ServiceLocator.h"
#include <fstream>

#include "InputManager.h"
#include "LifeLostScreen.h"
#include "MenuScreen.h"

void GameInstance::FillPlate()
{
	++m_FullPlates;
	if (m_FullPlates >= m_Plates)
	{
		auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
		dae::SceneManager::GetInstance().RemoveScene(scene);
		++m_LevelIdx;
		if (m_LevelIdx > 3)
			m_LevelIdx = 1;
		NextScreen{};
	}
}

void GameInstance::SetPlates(int amt)
{
	m_Plates = amt;
	m_FullPlates = 0;
}

void GameInstance::Hit(int lives)
{
	m_Lives = lives;
	LifeLostScreen{};
}

void GameInstance::ReloadLevel()
{
	if (m_LevelIdx == 1)
		LevelLoader::ReloadLevel("../Data/Levels/level1.json");
	else if (m_LevelIdx == 2)
		LevelLoader::ReloadLevel("../Data/Levels/level2.json");
	else if (m_LevelIdx == 3)
		LevelLoader::ReloadLevel("../Data/Levels/level3.json");
}

void GameInstance::Died(int points)
{
	m_Score = 0;
	if (m_HighScore < points)
		m_HighScore = points;
	SavePlayerToFile();
	std::sort(m_Players.begin(), m_Players.end(), [](const Player& a, const Player& b) {
		return a.score > b.score; });
	auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
	dae::SceneManager::GetInstance().RemoveScene(scene);
	DeathScreen{};
}


void GameInstance::LoadNextLevel()
{
	if (m_LevelIdx == 1)
		LevelLoader::LoadLevel("../Data/Levels/level1.json");
	else if (m_LevelIdx == 2)
		LevelLoader::LoadLevel("../Data/Levels/level2.json");
	else if (m_LevelIdx == 3)
		LevelLoader::LoadLevel("../Data/Levels/level3.json");
}

void GameInstance::EndGame()
{
	auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
	dae::SceneManager::GetInstance().RemoveScene(scene);
	dae::InputManager::GetInstance().RemoveCommands();
	MenuScreen{};
}

void GameInstance::StartGame()
{
	LoadPlayersFromFile();
}

void GameInstance::SkipLevel()
{
		dae::ServiceLocator::GetSoundSystem().StopAll();
		auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
		dae::SceneManager::GetInstance().RemoveScene(scene);
		++m_LevelIdx;
		if (m_LevelIdx > 3)
			m_LevelIdx = 1;
		LoadNextLevel();
}

void GameInstance::SavePlayerToFile() {
	std::ofstream outputFile("../Data/scores.txt", std::ios::app);

	if (outputFile.is_open()) {
		outputFile << m_Name << "," << m_HighScore << std::endl;
		outputFile.close();
	}
	else {
		std::cerr << "Unable to open the file for writing." << std::endl;
	}
}

void GameInstance::LoadPlayersFromFile() {
	std::ifstream inputFile("../Data/scores.txt");

	if (inputFile.is_open()) {
		Player player;
		while (getline(inputFile, player.name, ',')) {
			inputFile >> player.score;
			inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			m_Players.push_back(player);
		}
	}
	else {
		std::cerr << "Unable to open the file for reading." << std::endl;
	}
}



