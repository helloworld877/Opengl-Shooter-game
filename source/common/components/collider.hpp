#pragma once

#include "../ecs/component.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace our
{

    // This component denotes that any renderer should draw the given mesh using the given material at the transformation of the owning entity.
    class Collider : public Component
    {
    public:
        float radius = 1.0f;
        static std::string getID()
        {
            return "Collider";
        }

        // Receives the mesh & material from the AssetLoader by the names given in the json object
        void deserialize(const nlohmann::json &data) override;
    };

}
