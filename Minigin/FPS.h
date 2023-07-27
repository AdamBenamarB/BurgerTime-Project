#pragma once
#include <string>

#include "Component.h"

namespace dae
{
	class TextComponent;

	class FPS : public Component
	{
	public:
		FPS(GameObject* owner);
		void Update(float deltaTime) override;
		void FixedUpdate(float) override {};
		std::string GetFPS() const;
		void Test() { m_Test = !m_Test; }
	private:
		bool m_Test = true;
		int m_FrameCount{};
		float m_ElapsedSeconds{};
		int m_FPS{};
		TextComponent* m_TextComponent;
	};
}
