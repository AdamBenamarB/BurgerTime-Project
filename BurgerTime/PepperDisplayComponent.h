#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class TextComponent;
	class PepperDisplayComponent : public Component, public Observer
	{
	public:
		PepperDisplayComponent(GameObject* owner);
		void SetActorToDisplay(GameObject* obj);
		void Update(float) override{}
		void FixedUpdate(float) override {}

	protected:
		void OnNotify(const GameObject* obj, Event event) override;
	private:
		TextComponent* m_TextComponent{};
		GameObject* m_HealthActor{};
	};
}
