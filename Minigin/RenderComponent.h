#pragma once
#include "Component.h"
#include <string>
#include <memory>
namespace dae
{
	class Texture2D;
	class RenderComponent : public Component
	{
	public:
		RenderComponent(GameObject* owner);
		virtual void Render() const;
		void SetTexture(const std::shared_ptr<Texture2D> texture);
		void SetTexture(const std::string& filename);
		void SetDimensions(float width, float height);

		void SetEnabled(bool enabled) { m_Enabled = enabled; }
	private:
		std::shared_ptr<Texture2D> m_Texture;
		float m_Width{},
			m_Height{};
		bool m_UseDimensions{ false };
		bool m_Enabled{ true };
	};
}


