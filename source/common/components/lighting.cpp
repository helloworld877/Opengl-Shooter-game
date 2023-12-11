#include "lighting.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our
{
    // Reads sensitivities & speedupFactor from the given json object
    void LightingComponent::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;
        // setting light properties
        lightColor = data.value("lightColor", lightColor);
    }
}