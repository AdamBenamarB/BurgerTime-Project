#pragma once

#include "Structs.h"

namespace dae
{
	class Scene;
	class Lettuce
	{
	public:
		Lettuce(dae::Scene& scene, Vec2 loc);
		~Lettuce() = default;
		Lettuce(const Lettuce& other) = delete;
		Lettuce(Lettuce&& other) noexcept = delete;
		Lettuce& operator=(const Lettuce& other) = delete;
		Lettuce& operator=(Lettuce&& other) noexcept = delete;
	private:
		void Initialize(dae::Scene& scene, Vec2 loc);
	};
}
