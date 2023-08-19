#include "GameInstance.h"

#include <iostream>

#include "DeathScreen.h"
#include "SceneManager.h"
#include "LevelLoader.h"
#include "NextScreen.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include <fstream>

#include "LifeLostScreen.h"

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
	std::ofstream myfile;
	myfile.open("../Data/score.txt");
	myfile << m_HighScore;
	myfile.close();
	return;
}

void GameInstance::StartGame()
{
	std::fstream fs("../Data/score.txt", std::fstream::in);
	int k;
	while (fs >> k)
	{
		m_HighScore = k;
	}
	fs.close();
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
