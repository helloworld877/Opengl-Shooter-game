#include "lighting.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace our
{
    // Reads sensitivities & speedupFactor from the given json object
    void LightingComponent::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;
        // setting light properties from json file
        lightColor = data.value("lightColor", lightColor);
        lightType = data["lightType"].get<int>();
        lightAngle = glm::radians(data.value("lightAngle", glm::degrees(lightAngle)));
    }
}