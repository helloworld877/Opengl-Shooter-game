#pragma once

#include "../ecs/component.hpp"

namespace our
{

    // This component denotes that any renderer should draw the given mesh using the given material at the transformation of the owning entity.
    class LightingComponent : public Component
    {
    public:
        glm::vec3 lightColor;

        // The ID of this component type is "Lighting"
        static std::string getID() { return "Lighting"; }

        // Receives the mesh & material from the AssetLoader by the names given in the json object
        void deserialize(const nlohmann::json &data) override;
    };

}