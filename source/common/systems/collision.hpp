#pragma once
#include <vector>
#include <iostream>
#include "../ecs/world.hpp"
#include "../ecs/component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

#include "../components/collider.hpp"
#include "../application.hpp"

bool health = false;

namespace our
{

    class Collision
    {
        Application *app; // The application in which the state runs
    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application *app)
        {
            this->app = app;
        }

        // This should be called every frame to update all entities containing a collider component
        void update(World *world, float deltaTime)
        {
            // vector to store all colliders
            std::vector<Collider *> all_colliders;

            // camera pointer
            Entity *camera = nullptr;

            for (auto entity : world->getEntities())
            {
                auto collider = entity->getComponent<Collider>();
                if (collider)
                {
                    // adding all colliders to the vector
                    all_colliders.push_back(collider);
                }
                // get camera (player) entity
                if (entity->name == "player")
                {
                    camera = entity;

                    if (camera->localTransform.position.x < -10 || camera->localTransform.position.x > 10)
                    {
                        std::cout << "out of bounds\n";
                    }
                    if (camera->localTransform.position.z < -10 || camera->localTransform.position.z > 10)
                    {
                        std::cout << "out of bounds\n";
                    }
                }
            }

            // loop on all colliders
            for (auto first : all_colliders)
            {
                for (auto second : all_colliders)
                {
                    // we must not check for collisions in the same object
                    if (first != second)
                    {
                        // getting the center of entity
                        auto center1 = first->getOwner()->getLocalToWorldMatrix() * glm::vec4(0, 0, 0, 1);
                        auto center2 = second->getOwner()->getLocalToWorldMatrix() * glm::vec4(0, 0, 0, 1);

                        auto name1 = first->getOwner()->name;
                        auto name2 = second->getOwner()->name;

                        auto dist = glm::distance(center1, center2);
                        if (dist < 0)
                        {
                            dist = dist * -1;
                        }

                        if (first->radius + second->radius >= dist)
                        {
                            // collision here
                            std::cout << "collide between " << name1 << " and " << name2 << "\n";
                            app->changeState("lose");
                        }
                    }
                }
            };
        }
    };
}
