#pragma once


struct Vec2;

namespace dae
{
	class Scene;
	class GameObject;
	class MrEgg
	{
	public:
		MrEgg(dae::Scene& scene, Vec2 loc, GameObject* peter);
		~MrEgg() = default;
		MrEgg(const MrEgg& other) = delete;
		MrEgg(MrEgg&& other) noexcept = delete;
		MrEgg& operator=(const MrEgg& other) = delete;
		MrEgg& operator=(MrEgg&& other) noexcept = delete;

	private:
		void Initialize(dae::Scene& scene, Vec2 loc, GameObject* peter);

		float m_Height{ 32 },
			m_Width{ 32 };
	};
}
