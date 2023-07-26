#pragma once
#include <memory>
#include <string>

#include "Component.h"

namespace dae
{
	struct Color
	{
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		uint8_t alpha;
	};
	class Font;
	class Texture2D;
	class RenderComponent;

	class TextComponent : public Component
	{
	public:
		void Update(float deltaTime) override;
		void FixedUpdate(float) override {};

		void SetText(const std::string& text);
		void SetFont(const std::shared_ptr<Font>& font);
		void SetColor(float r, float g, float b, float a = 1);

		TextComponent(GameObject* owner);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent & other) = delete;
		TextComponent(TextComponent && other) = delete;
		TextComponent& operator=(const TextComponent & other) = delete;
		TextComponent& operator=(TextComponent && other) = delete;
	private:
		RenderComponent* m_RenderComponent{};
		Color m_Color{ 255,255,255,255 };
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;

	};
}


