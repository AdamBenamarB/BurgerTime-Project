#pragma once

#include "Component.h"
#include "Structs.h"

namespace dae {
    class PlatformComponent : public Component
    {
    public:
        void Update(float) override{}
        void FixedUpdate(float) override{}
        PlatformComponent(GameObject* owner);
    	Vec2 GetFloorPos() const;
    };
}
