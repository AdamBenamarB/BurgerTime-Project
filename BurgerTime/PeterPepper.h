#pragma once


struct Vec2;

namespace dae
{
	class PointsComponent;
	class Scene;
	class GameObject;
	class PeterPepper
	{
	public:
		PeterPepper(dae::Scene& scene, Vec2 loc);
		~PeterPepper() = default;
		PeterPepper(const PeterPepper& other) = delete;
		PeterPepper(PeterPepper&& other) noexcept = delete;
		PeterPepper& operator=(const PeterPepper& other) = delete;
		PeterPepper& operator=(PeterPepper&& other) noexcept = delete;

		GameObject* GetGameObject();

	private:
		void Initialize(dae::Scene& scene, Vec2 loc);

		float m_Height{ 16 },
			m_Width{ 16 };
		GameObject* m_Peter{};

	};
}