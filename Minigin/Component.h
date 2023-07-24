#pragma once
namespace dae
{
	class GameObject;
	class Component
	{
	public:
		Component(GameObject* owner);
		~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) noexcept = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) noexcept = delete;

		virtual void FixedUpdate(float deltaTime);
		virtual void Update(float deltaTime);

		void SetOwner(GameObject* owner) { m_Owner = owner; }
		GameObject* GetOwner() const { return m_Owner; }
	protected:
		GameObject* m_Owner;
	};
}
