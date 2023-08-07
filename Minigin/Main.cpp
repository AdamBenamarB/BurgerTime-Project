#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "CollisionComponent.h"
#include "FPS.h"
#include "GameObject.h"
#include "HealthDisplayComponent.h"
#include "HealthDisplayComponent.h"
#include "Input.h"
#include "InputManager.h"
#include "Minigin.h"
#include "PeterPepperComponent.h"
#include "PlatformComponent.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"

//
//int main(int, char*[]) {
//	dae::Minigin engine("../Data/");
//	engine.Run(load);
//    return 0;
//}