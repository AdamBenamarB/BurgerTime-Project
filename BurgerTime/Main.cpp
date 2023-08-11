#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "CollisionComponent.h"
#include "FPS.h"
#include "GameObject.h"
#include "HealthDisplayComponent.h"
#include "Input.h"
#include "InputManager.h"
#include "Ladder.h"
#include "MrHotDog.h"
#include "PeterPepper.h"
#include "PeterPepperComponent.h"
#include "Platform.h"
#include "PlatformComponent.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Tags.h"
#include "TextComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Ladder
	dae::Ladder(scene,Vec2{150,16});
	dae::Ladder(scene, Vec2{ 150,32 });

	for(int x{}; x < 11; ++x)
	for (int i{}; i < 18; ++i)
	{
		dae::Platform(scene, Vec2{ float(i * 16),float(32*x) });
	}
	
	dae::PeterPepper peter{ scene,Vec2{10,0} };
	dae::MrHotDog{ scene,Vec2{80,0},peter.GetGameObject() };
	
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}