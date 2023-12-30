#pragma once

#include "../ecs/world.hpp"
#include "../components/movement.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <iostream>
namespace our
{

    // The movement system is responsible for moving every entity which contains a MovementComponent.
    // This system is added as a simple example for how use the ECS framework to implement logic.
    // For more information, see "common/components/movement.hpp"
    class MovementSystem
    {
    public:
        // This should be called every frame to update all entities containing a MovementComponent.
        void update(World *world, float deltaTime)
        {

            Entity *player = nullptr;
            for (auto entity : world->getEntities())
            {
                if (entity->name == "player")
                {
                    player = entity;
                }
            }

            // For each entity in the world
            for (auto entity : world->getEntities())
            {
                // Get the movement component if it exists
                MovementComponent *movement = entity->getComponent<MovementComponent>();

                // if the entity is an enemy orient them towards the player
                if (entity->name == "enemy")
                {
                    // make the enemy entity look towards the player entity
                    glm::vec3 direction;
                    direction.x = player->localTransform.position.x - entity->localTransform.position.x;
                    direction.y = player->localTransform.position.y - entity->localTransform.position.y;
                    direction.z = player->localTransform.position.z - entity->localTransform.position.z;

                    // Calculate the yaw (heading) angle
                    float yaw = atan2(-direction.x, direction.z);

                    // Calculate the pitch (elevation) angle
                    float distanceXZ = sqrt(direction.x * direction.x + direction.z * direction.z);
                    float pitch = atan2(direction.y, distanceXZ);

                    // Update the enemy's rotation based on the calculated angles
                    entity->localTransform.rotation.x = pitch; // Set pitch rotation
                    entity->localTransform.rotation.y = -yaw;  // Set yaw rotation
                    entity->localTransform.rotation.z = 0.0f;  // Assuming no roll rotation

                    float moveX = -sin(yaw) * 2.0 * deltaTime;
                    float moveZ = cos(yaw) * 2.0 * deltaTime;

                    // Update the enemy's position based on the movement components
                    entity->localTransform.position.x += moveX;
                    entity->localTransform.position.z += moveZ;
                }
                // If the movement component exists
                if (movement && entity->name != "enemy")
                {
                    // Change the position and rotation based on the linear & angular velocity and delta time.
                    entity->localTransform.position += deltaTime * movement->linearVelocity;
                    entity->localTransform.rotation += deltaTime * movement->angularVelocity;
                }
            }
        }
    };

}
