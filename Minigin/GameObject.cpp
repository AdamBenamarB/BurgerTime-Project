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

void dae::GameObject::SetParent(GameObject* parent, bool worldPosStays)
{

	/*Remove itself as a child from the previous parent(if any).
		• Set the given parent on itself.
		• Add itself as a child to the given parent.
		• Update position, rotationand scale*/

	if(m_Parent)
	{
		m_Parent->RemoveChild(this);
	}

	m_Parent = parent;

	m_Parent->AddChild(this);

	if(!worldPosStays)
	{

		GetTransform()->SetLocalPosition(parent->GetTransform()->GetWorldPosition());
	}
}

void dae::GameObject::AddChild(GameObject* child)
{
	/*AddChild has to do four things
		• Remove the given child from the child's previous parent
		• Set itself as parent of the child
		• Add the child to its children list.
		• Update position, rotationand scale*/
	auto previousParent = child->GetParent();

	if(previousParent != this)
	{
		previousParent->RemoveChild(child);
	}

	m_Children.push_back(child);

}

void dae::GameObject::RemoveChild(GameObject* child)
{
	m_Children.erase(std::find(m_Children.begin(), m_Children.end(), child));
	child->SetParent(nullptr);
}
