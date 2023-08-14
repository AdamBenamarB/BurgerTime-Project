#pragma once
#include "GameObject.h"

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
	private:
		void CheckPos();
		bool m_CheckedPos = false;
		bool m_IsBottom = true;
		bool m_IsTop = true;
	};

}