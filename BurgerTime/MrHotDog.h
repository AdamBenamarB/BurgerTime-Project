#pragma once


struct Vec2;

namespace dae
{
	class Scene;
	class GameObject;
	class MrHotDog
	{
	public:
		MrHotDog(dae::Scene& scene, Vec2 loc, GameObject* peter);
		~MrHotDog() = default;
		MrHotDog(const MrHotDog& other) = delete;
		MrHotDog(MrHotDog&& other) noexcept = delete;
		MrHotDog& operator=(const MrHotDog& other) = delete;
		MrHotDog& operator=(MrHotDog&& other) noexcept = delete;

	private:
		void Initialize(dae::Scene& scene, Vec2 loc, GameObject* peter);

		float m_Height{ 16 },
			m_Width{ 16 };
	};
}
