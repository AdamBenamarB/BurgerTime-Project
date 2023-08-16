#pragma once
#include "Component.h"

namespace dae {
	class LadderComponent : public Component
	{
	public:
		LadderComponent(GameObject* owner) :Component{ owner } {}
		void Update(float deltaTime) override{}
		void FixedUpdate(float deltaTime) override{}

		bool OnTop(GameObject* go);
		bool OnBottom(GameObject* go);
		bool IsBottom();
		bool IsTop();

		bool InRange(GameObject* go);
	private:
		void CheckPos();
		bool m_CheckedPos = false;
		bool m_IsBottom = true;
		bool m_IsTop = true;
		float m_ClimbRange = 8.f;
	};

}
