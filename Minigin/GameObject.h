#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Transform.h"

enum class Tag;

namespace dae
{
	class Component;
	class Texture2D;

	class GameObject final
	{
	public:
		GameObject() { m_Transform = AddComponent<Transform>(); };
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void FixedUpdate(float deltaTime);
		void Update(float deltaTime);
		void Render() const;

		GameObject* GetParent() const{ return m_Parent; }
		void SetParent(GameObject* parent, bool keepWorldPos = false);
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);

		void SetTag(Tag tag) { m_Tag = tag; }
		const Tag& GetTag() const { return m_Tag; }
		std::vector<GameObject*> GetChildren() const { return m_Children; }

		Transform* GetTransform() { return m_Transform; }

		template<typename T> T* AddComponent();
		template<typename T> T* GetComponent() const;
		template<typename T> std::vector<T*> GetComponents() const;
		template<typename T> void RemoveComponent();


	private:
		GameObject* m_Parent = nullptr;
		std::vector<GameObject*> m_Children{};
		Transform* m_Transform;
		std::vector<std::shared_ptr<Component>> m_Components{};
		Tag m_Tag{};
	};
}

template <typename T>
T* dae::GameObject::AddComponent()
{
	if (std::is_base_of<Component, T>())
	{

		std::shared_ptr < T > ptr = std::make_shared<T>(this);
		m_Components.push_back(ptr);
		return ptr.get();
	}
	else return nullptr;
}

template <typename T>
T* dae::GameObject::GetComponent() const
{
	for (std::shared_ptr<Component> comp : m_Components)
	{
		if (dynamic_cast<T*>(comp.get()))
		{
			return (T*)comp.get();
		}

	}
	return nullptr;
}

template <typename T>
std::vector<T*> dae::GameObject::GetComponents() const
{
	std::vector<T*> comps{};
	for (std::shared_ptr<Component> comp : m_Components)
	{
		if (dynamic_cast<T*>(comp.get()))
		{
			comps.push_back((T*)comp.get());
		}
	}
	return comps;
}

template<typename T>
void dae::GameObject::RemoveComponent()
{
	for (auto it = m_Components.begin(); it < m_Components.end();)
	{
		if (typeid(**it) == typeid(T))
		{
			it = m_Components.erase(it);
		}
		else
		{
			++it;
		}
	}

}