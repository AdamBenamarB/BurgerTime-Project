#include "LevelLoader.h"
#include <fstream>
#include <rapidjson.h>
#include <document.h>

#include "BottomBun.h"
#include "Bun.h"
#include "Cheese.h"
#include "EnemySpawner.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "HealthDisplayComponent.h"
#include "InputManager.h"
#include "istreamwrapper.h"
#include "Ladder.h"
#include "Lettuce.h"
#include "Patty.h"
#include "PepperComponent.h"
#include "PepperDisplayComponent.h"
#include "PeterPepper.h"
#include "PeterPepperJr.h"
#include "Plate.h"
#include "Platform.h"
#include "PlayerHotDog.h"
#include "PointsComponent.h"
#include "PointsDisplayComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "Tomato.h"

void LevelLoader::ReloadLevel(const std::string& fileLoc)
{
	
	dae::ServiceLocator::GetSoundSystem().StopAll();
	auto& sceneDel = dae::SceneManager::GetInstance().GetActiveScene();
	dae::SceneManager::GetInstance().RemoveScene(sceneDel);

	int lives = GameInstance::GetInstance().GetLives();

	dae::InputManager::GetInstance().RemoveCommands();
	auto& scene = dae::SceneManager::GetInstance().CreateScene("LEVEL");
	int music = dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/music.wav");
	dae::ServiceLocator::GetSoundSystem().Play(music, 100, true);
	if (std::ifstream is{ fileLoc })
	{
		rapidjson::IStreamWrapper isw{ is };
		rapidjson::Document jsonDoc;
		jsonDoc.ParseStream(isw);

		std::vector<Vec2> bounds{};
		int plates{};
		dae::GameObject* petergo = nullptr;

		using rapidjson::Value;
		for (Value::ConstValueIterator itr = jsonDoc.Begin(); itr != jsonDoc.End(); ++itr)
		{
			const Value& pos = *itr;
			std::string type = pos["type"].GetString();
			const Value& locs = pos["positions"].GetArray();
			for (rapidjson::SizeType i = 0; i < locs.Size(); i++)
			{
				const Value& x = locs[i][0];
				const Value& y = locs[i][1];

				if (type == "platform")
				{
					dae::Platform{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "ladder")
				{
					dae::Ladder{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "bun")
				{
					dae::Bun{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "lettuce")
				{
					dae::Lettuce{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "patty")
				{
					dae::Patty{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "cheese")
				{
					dae::Cheese{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "tomato")
				{
					dae::Tomato{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "bottombun")
				{
					dae::BottomBun{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "plate")
				{
					dae::Plate{ scene,{x.GetFloat(),y.GetFloat()} };
					++plates;
				}
				if (type == "peter")
				{
					if (GameInstance::GetInstance().GetGameMode() != GameMode::singleplayer)
					{
						dae::PeterPepper peter{ scene,{x.GetFloat(),y.GetFloat()},false };
						petergo = peter.GetGameObject();
						petergo->GetComponent<dae::HealthComponent>()->SetLives(lives);

						auto go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(80, 850, 0);

						auto pointsdisp = go->AddComponent<dae::PointsDisplayComponent>();
						pointsdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::PointsComponent>()->AddObserver(pointsdisp);
						scene.Add(go);

						go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(550, 850, 0);
						auto healthdisp = go->AddComponent<dae::HealthDisplayComponent>();
						healthdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::HealthComponent>()->AddObserver(healthdisp);
						scene.Add(go);

						go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(560, 820, 0);
						auto pepperdisp = go->AddComponent<dae::PepperDisplayComponent>();
						pepperdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::PepperComponent>()->AddObserver(pepperdisp);
						scene.Add(go);
					}
					else
					{
						dae::PeterPepper peter{ scene,{x.GetFloat(),y.GetFloat()} };
						petergo = peter.GetGameObject();
						petergo->GetComponent<dae::HealthComponent>()->SetLives(lives);

						auto go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(80, 850, 0);

						auto pointsdisp = go->AddComponent<dae::PointsDisplayComponent>();
						pointsdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::PointsComponent>()->AddObserver(pointsdisp);
						scene.Add(go);

						go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(550, 850, 0);
						auto healthdisp = go->AddComponent<dae::HealthDisplayComponent>();
						healthdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::HealthComponent>()->AddObserver(healthdisp);
						scene.Add(go);

						go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(560, 820, 0);
						auto pepperdisp = go->AddComponent<dae::PepperDisplayComponent>();
						pepperdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::PepperComponent>()->AddObserver(pepperdisp);
						scene.Add(go);
					}
				}
				if (type == "peterjr")
				{
					if (GameInstance::GetInstance().GetGameMode() == GameMode::coop)
					{
						dae::PeterPepperJr peter{ scene,{x.GetFloat(),y.GetFloat()} };
						auto peterjr = peter.GetGameObject();
						peterjr->GetComponent<dae::PeterPepperComponent>()->SetOtherPeter(petergo);

						auto go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(560, 800, 0);
						auto pepperdisp = go->AddComponent<dae::PepperDisplayComponent>();
						pepperdisp->SetActorToDisplay(peterjr);
						peterjr->GetComponent<dae::PepperComponent>()->AddObserver(pepperdisp);
						scene.Add(go);
					}

				}
				if (type == "playerdog")
				{
					if (GameInstance::GetInstance().GetGameMode() == GameMode::versus)
					{
						dae::PlayerHotDog{ scene,{x.GetFloat(),y.GetFloat()} };
					}
				}
				if (type == "enemy")
				{
						EnemySpawner{ scene,{x.GetFloat(),y.GetFloat()} };
				}
			}
		}
		//scene.SetBounds({ bounds[0], bounds[1] });
		GameInstance::GetInstance().SetPlates(plates);
	}
}

void LevelLoader::LoadLevel(const std::string& fileLoc)
{
	dae::InputManager::GetInstance().RemoveCommands();
	auto& scene = dae::SceneManager::GetInstance().CreateScene("LEVEL");
	int music = dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/music.wav");
	dae::ServiceLocator::GetSoundSystem().Play(music, 100, true);
	if (std::ifstream is{ fileLoc })
	{
		rapidjson::IStreamWrapper isw{ is };
		rapidjson::Document jsonDoc;
		jsonDoc.ParseStream(isw);

		std::vector<Vec2> bounds{};
		int plates{};
		dae::GameObject* petergo = nullptr;

		using rapidjson::Value;
		for (Value::ConstValueIterator itr = jsonDoc.Begin(); itr != jsonDoc.End(); ++itr)
		{
			const Value& pos = *itr;
			std::string type = pos["type"].GetString();
			const Value& locs = pos["positions"].GetArray();
			for (rapidjson::SizeType i = 0; i < locs.Size(); i++)
			{
				const Value& x = locs[i][0];
				const Value& y = locs[i][1];

				if (type == "platform")
				{
					dae::Platform{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "ladder")
				{
					dae::Ladder{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "bun")
				{
					dae::Bun{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "lettuce")
				{
					dae::Lettuce{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "patty")
				{
					dae::Patty{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "cheese")
				{
					dae::Cheese{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "tomato")
				{
					dae::Tomato{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "bottombun")
				{
					dae::BottomBun{ scene,{x.GetFloat(),y.GetFloat()} };
				}
				if (type == "plate")
				{
					dae::Plate{ scene,{x.GetFloat(),y.GetFloat()} };
					++plates;
				}
				if (type == "peter")
				{
					if (GameInstance::GetInstance().GetGameMode() != GameMode::singleplayer)
					{
						dae::PeterPepper peter{ scene,{x.GetFloat(),y.GetFloat()},false };
						petergo = peter.GetGameObject();

						auto go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(80, 850, 0);

						auto pointsdisp = go->AddComponent<dae::PointsDisplayComponent>();
						pointsdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::PointsComponent>()->AddObserver(pointsdisp);
						scene.Add(go);

						go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(550, 850, 0);
						auto healthdisp = go->AddComponent<dae::HealthDisplayComponent>();
						healthdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::HealthComponent>()->AddObserver(healthdisp);
						scene.Add(go);

						go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(560, 820, 0);
						auto pepperdisp = go->AddComponent<dae::PepperDisplayComponent>();
						pepperdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::PepperComponent>()->AddObserver(pepperdisp);
						scene.Add(go);
					}
					else
					{
						dae::PeterPepper peter{ scene,{x.GetFloat(),y.GetFloat()} };
						petergo = peter.GetGameObject();

						auto go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(80, 850, 0);

						auto pointsdisp = go->AddComponent<dae::PointsDisplayComponent>();
						pointsdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::PointsComponent>()->AddObserver(pointsdisp);
						scene.Add(go);

						go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(550, 850, 0);
						auto healthdisp = go->AddComponent<dae::HealthDisplayComponent>();
						healthdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::HealthComponent>()->AddObserver(healthdisp);
						scene.Add(go);

						go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(560, 820, 0);
						auto pepperdisp = go->AddComponent<dae::PepperDisplayComponent>();
						pepperdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::PepperComponent>()->AddObserver(pepperdisp);
						scene.Add(go);
					}
				}
				if (type == "peterjr")
				{
					if (GameInstance::GetInstance().GetGameMode() == GameMode::coop)
					{
						dae::PeterPepperJr peter{ scene,{x.GetFloat(),y.GetFloat()} };
						auto peterjr = peter.GetGameObject();
						peterjr->GetComponent<dae::PeterPepperComponent>()->SetOtherPeter(petergo);

						auto go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(560, 800, 0);
						auto pepperdisp = go->AddComponent<dae::PepperDisplayComponent>();
						pepperdisp->SetActorToDisplay(peterjr);
						peterjr->GetComponent<dae::PepperComponent>()->AddObserver(pepperdisp);
						scene.Add(go);
					}

				}
				if (type == "playerdog")
				{
					if (GameInstance::GetInstance().GetGameMode() == GameMode::versus)
					{
						dae::PlayerHotDog{ scene,{x.GetFloat(),y.GetFloat()} };
					}

				}
				if (type == "enemy")
				{
					EnemySpawner{ scene,{x.GetFloat(),y.GetFloat()} };
				}
			}
		}
		GameInstance::GetInstance().SetPlates(plates);
	}
}
