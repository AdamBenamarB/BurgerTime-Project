#pragma once
namespace dae
{
	class GameObject;
	class Component
	{
	public:
		~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) noexcept = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) noexcept = delete;

		virtual void FixedUpdate(float deltaTime) = 0;
		virtual void Update(float deltaTime) = 0;
	private:
		GameObject* m_Owner;
	protected:
		explicit Component(GameObject* owner) : m_Owner(owner){};
		GameObject* GetOwner() const { return m_Owner; }
	};
}
