#include "collider.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace our
{
    // Reads sensitivities & speedupFactor from the given json object
    void Collider::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;
        radius = data.value("radius", 1.0f);
    }
}