#pragma once
#include "RenderComponent.h"
#include "Structs.h"
#include <vector>
namespace dae
{

	class Texture2D;
	class AnimatedRenderComponent : public RenderComponent
	{
	public:
		AnimatedRenderComponent(GameObject* owner);
		void Render() const override;
		void Update(float deltaTime) override;

		int AddClip(int colAmt, bool looping);
		void SetSpriteDimensions(float width, float height);

		void SetClip(int idx);
	private:
		struct AnimationClip
		{
			int colAmt;
			bool looping = true;
		};

		std::vector<AnimationClip> m_Clips{};
		Rect m_SrcRct{};

		float m_SpriteWidth{},
			m_SpriteHeight{};

		int m_ColNr{};
		int m_AnimIdx{};
		int m_FPS{ 10 };

		float m_ElapsedSec{};


	};
}


