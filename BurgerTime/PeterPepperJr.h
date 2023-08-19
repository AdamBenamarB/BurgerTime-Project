#pragma once


struct Vec2;

namespace dae
{
	class PointsComponent;
	class Scene;
	class GameObject;
	class PeterPepperJr
	{
	public:
		PeterPepperJr(dae::Scene& scene, Vec2 loc, bool keyboardControls = true);
		~PeterPepperJr() = default;
		PeterPepperJr(const PeterPepperJr& other) = delete;
		PeterPepperJr(PeterPepperJr&& other) noexcept = delete;
		PeterPepperJr& operator=(const PeterPepperJr& other) = delete;
		PeterPepperJr& operator=(PeterPepperJr&& other) noexcept = delete;

		GameObject* GetGameObject();

	private:
		void Initialize(dae::Scene& scene, Vec2 loc, bool keyboardControls);

		float m_Height{ 32 },
			m_Width{ 32 };
		GameObject* m_PeterJr{};

	};
}
