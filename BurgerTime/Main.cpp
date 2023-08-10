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
	dae::Ladder(scene,Vec2{150,10});
	dae::Ladder(scene, Vec2{ 150,26 });

	for (int i{}; i < 11; ++i)
	{
		dae::Platform(scene, Vec2{ float(i * 16),10 });
	}
	
	dae::PeterPepper{ scene,Vec2{10,10} };
	
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}