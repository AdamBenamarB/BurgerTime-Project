#include "Game.h"

#include "GameInstance.h"
#include "NextScreen.h"

void Game::LoadGame()
{
	GameInstance::GetInstance().StartGame();
	NextScreen{};
}


void Game::Cleanup()
{
	GameInstance::GetInstance().EndGame();
	Minigin::Cleanup();
}
