#include <string>
#include "GameObject.h"

#include "Component.h"
#include "RenderComponent.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::FixedUpdate(float deltaTime)
{
	for(std::shared_ptr<Component> comp : m_Components)
	{
		comp->FixedUpdate(deltaTime);
	}
}

void dae::GameObject::Update(float deltaTime)
{
	for (std::shared_ptr<Component> comp : m_Components)
	{
		comp->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	if(auto render = GetComponent<RenderComponent>())
	{
		render->Render();
	}
}
