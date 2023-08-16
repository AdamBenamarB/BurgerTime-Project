#pragma once

#include "Structs.h"

namespace dae
{
	class Scene;
	class Bun
	{
	public:
		Bun(dae::Scene& scene, Vec2 loc);
		~Bun() = default;
		Bun(const Bun& other) = delete;
		Bun(Bun&& other) noexcept = delete;
		Bun& operator=(const Bun& other) = delete;
		Bun& operator=(Bun&& other) noexcept = delete;
	private:
		void Initialize(dae::Scene& scene, Vec2 loc);
	};
}
