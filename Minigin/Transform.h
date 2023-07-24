#pragma once
#include <glm/glm.hpp>

#include "Component.h"

namespace dae
{
	class Transform : public Component
	{
	public:
		Transform(GameObject* obj);
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_Position{};
	};
}
