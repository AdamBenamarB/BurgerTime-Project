#include "FPS.h"
#include "GameObject.h"
#include "TextComponent.h"

dae::FPS::FPS(GameObject* owner)
	:Component{ owner }
{
	m_TextComponent = GetOwner()->GetComponent<TextComponent>();
	m_TextComponent->SetText("0");
	m_TextComponent->SetColor(0, 1, 0);
}

void dae::FPS::Update(float deltaTime)
{
	if (m_Test)
	{
		auto pos = GetOwner()->GetTransform()->GetWorldPosition();
		pos.x += 1;
		GetOwner()->GetTransform()->SetLocalPosition(pos);
	}
	++m_FrameCount;
	m_ElapsedSeconds += deltaTime;
	if (m_ElapsedSeconds >= 1)
	{
		m_FPS = int(m_FrameCount / m_ElapsedSeconds);
		m_FrameCount = 0;
		m_ElapsedSeconds = 0;
		m_TextComponent->SetText(GetFPS() + " FPS");
	}
}

std::string dae::FPS::GetFPS() const
{
	return std::to_string(m_FPS);
}