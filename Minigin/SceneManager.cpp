#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::FixedUpdate(float deltaTime)
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate(deltaTime);
	}
}


void dae::SceneManager::Update(float deltaTime)
{
	if (m_ToRemove)
	{
		if (m_ActiveScene == m_ToRemove)
			m_ActiveScene = nullptr;

		for (int i{}; i < (int)m_Scenes.size(); ++i)
		{
			if (m_Scenes[i].get() == m_ToRemove)
			{
				m_Scenes[i].reset();
				m_ToRemove = nullptr;
				break;
			}
		}
	}
	for(auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	m_ActiveScene = scene.get();
	return *scene;
}

void dae::SceneManager::SetActiveScene(std::string sceneName)
{
	for (auto& scene : m_Scenes)
		if (scene->GetName().compare(sceneName) == 0)
			m_ActiveScene = scene.get();
}

void dae::SceneManager::RemoveScene(Scene& scene)
{
	Scene* p = std::addressof(scene);
	if (p)
		m_ToRemove = p;
}
