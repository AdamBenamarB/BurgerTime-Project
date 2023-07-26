#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FPS.h"
#include "GameObject.h"
#include "Minigin.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	auto rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("logo.tga");
	go->GetTransform()->SetLocalPosition(216, 180,0);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	auto text = go->AddComponent<dae::TextComponent>();
	text->SetText("Programming 4 Assignment");
	text->SetFont(font);
	go->GetTransform()->SetLocalPosition(80, 20,0);
	scene.Add(go);

	auto gg = go;

	go = std::make_shared<dae::GameObject>();
	text = go->AddComponent<dae::TextComponent>();
	text->SetFont(font);
	go->AddComponent<dae::FPS>();
	go->GetTransform()->SetLocalPosition(10, 10, 0);
	scene.Add(go);

	gg->SetParent(go.get());


}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}