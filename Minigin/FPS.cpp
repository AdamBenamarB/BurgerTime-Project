#include "FPS.h"
#include "GameObject.h"
#include "TextComponent.h"

dae::FPS::FPS(GameObject* owner)
	:Component{ owner }
{
	m_TextComponent = GetOwner()->GetComponent<TextComponent>();
	m_TextComponent->SetText("0");
}

void dae::FPS::Update(float deltaTime)
{
	++m_FrameCount;
	m_ElapsedSeconds += deltaTime;
	if (m_ElapsedSeconds >= 1)
	{
		m_FPS = int(m_FrameCount / m_ElapsedSeconds);
		m_FrameCount = 0;
		m_ElapsedSeconds = 0;
		m_TextComponent->SetText(GetFPS());
	}
}

std::string dae::FPS::GetFPS() const
{
	return std::to_string(m_FPS);
}