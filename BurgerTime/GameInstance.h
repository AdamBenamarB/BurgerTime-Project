#pragma once
#include "Singleton.h"

enum class GameMode
{
	singleplayer,
	coop,
	versus
};

class GameInstance : public dae::Singleton<GameInstance>
{
public:
	void SetPlates(int amt);

	void FillPlate();

	void Died(int points);

	int GetScore()const { return m_Score; }
	int GetHighScore()const { return m_HighScore; }
	void LoadNextLevel();

	int GetLevelNr()const { return m_LevelIdx; }

	void StartGame();
	void EndGame();

	void SetGameMode(GameMode gamemode) { m_Gamemode = gamemode; }
	GameMode GetGameMode() const { return m_Gamemode; }

private:
	int m_LevelIdx{ 1 };

	int m_Plates{},
		m_FullPlates{};

	int m_Score{};
	int m_HighScore{};

	GameMode m_Gamemode = GameMode::singleplayer;
};