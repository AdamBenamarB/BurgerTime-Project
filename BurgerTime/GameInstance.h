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

	void Hit(int lives);
	void Died(int points);

	int GetScore()const { return m_Score; }
	int GetHighScore()const { return m_HighScore; }

	void ReloadLevel();
	void LoadNextLevel();
	void SkipLevel();

	int GetLevelNr()const { return m_LevelIdx; }
	int GetLives() const { return m_Lives; }
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

	int m_Lives{};

	GameMode m_Gamemode = GameMode::coop;
};