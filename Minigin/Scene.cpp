#include "Scene.h"

#include <iostream>

#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_Objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), object), m_Objects.end());
}

void Scene::RemoveAll()
{
	m_Objects.clear();
}

void Scene::FixedUpdate(float deltaTime)
{
	for (int i{}; i < (int)m_Objects.size(); ++i)
	{
		m_Objects[i]->FixedUpdate(deltaTime);
	}
}

void Scene::Update(float deltaTime)
{
	for(int i{}; i < (int)m_Objects.size(); ++i)
	{
		m_Objects[i]->Update(deltaTime);
	}
}

void Scene::Render() const
{
	for (int i{}; i < (int)m_Objects.size(); ++i)
	{
		m_Objects[i]->Render();
	}
}

