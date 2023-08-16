#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Bun.h"
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
#include "Plate.h"
#include "Platform.h"
#include "PlatformComponent.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Tags.h"
#include "TextComponent.h"
#include "Tomato.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Ladder
	dae::Ladder(scene,Vec2{200,32});
	dae::Ladder(scene, Vec2{ 200,64 });
	dae::Ladder(scene, Vec2{ 100,32 });
	dae::Ladder(scene, Vec2{ 100,64 });
	dae::Ladder(scene, Vec2{ 240,96 });
	dae::Ladder(scene, Vec2{ 240,128 });
	dae::Ladder(scene, Vec2{ 240,160 });
	dae::Ladder(scene, Vec2{ 240,192 });
	dae::Ladder(scene, Vec2{ 240,224 });


	for(int x{}; x < 11; ++x)
	for (int i{}; i < 18; ++i)
	{
		dae::Platform(scene, Vec2{ float(i * 32),float(64*x) });
	}
	
	dae::PeterPepper peter{ scene,Vec2{480,0} };
	dae::MrHotDog{ scene,Vec2{80,0},peter.GetGameObject() };
	
	dae::Tomato(scene, Vec2{ 320,0 });

	dae::Plate(scene, Vec2{ 320, 220 });
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}