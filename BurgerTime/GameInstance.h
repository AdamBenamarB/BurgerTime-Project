#pragma once
#include "Singleton.h"

class GameInstance : public dae::Singleton<GameInstance>
{
public:
	void SetPlates(int amt);

	void FillPlate();

	void Died(int points);

	int GetScore()const { return m_Score; }
	int GetHighScore()const { return m_HighScore; }
	void LoadNextLevel();

	int GetLevelNr() { return m_LevelIdx; }

	void StartGame();
	void EndGame();
private:
	int m_LevelIdx{ 1 };

	int m_Plates{},
		m_FullPlates{};

	int m_Score{};
	int m_HighScore{};
};