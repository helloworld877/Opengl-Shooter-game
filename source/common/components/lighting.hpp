#pragma once

#include "../ecs/component.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace our
{

    // This component denotes that any renderer should draw the given mesh using the given material at the transformation of the owning entity.
    class LightingComponent : public Component
    {
    public:
        glm::vec3 lightColor = glm::vec3(0, 0, 0);
        // 0 -> Directional
        // 1 -> Point
        // 2 -> spot
        int lightType = 0;

        // The ID of this component type is "Light"
        static std::string getID() { return "Light"; }

        // Receives the mesh & material from the AssetLoader by the names given in the json object
        void deserialize(const nlohmann::json &data) override;
    };

}