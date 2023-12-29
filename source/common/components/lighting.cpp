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
        // not directional light
        if (lightType != 0)
        {
            attenuation = glm::vec3(data.value("attenuation", glm::vec3(1, 0, 0)));
        }
        // if it was a spotlight
        if (lightType == 2)
        {
            inner_angle = glm::radians((float)data.value("inner_angle", 10));
            outer_angle = glm::radians((float)data.value("outer_angle", 30));
        }
    }
}