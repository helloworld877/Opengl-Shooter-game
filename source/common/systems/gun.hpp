#pragma once
#include <vector>
#include <iostream>
#include "../ecs/world.hpp"
#include "../ecs/component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

// #include "../components/collider.hpp"
#include "../application.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>

namespace our
{

    class Gun
    {
        Application *app; // The application in which the state runs
        // glm::vec3 PrevPosition = {0, 0, 0};
        Mix_Chunk *sound;
        bool mouseClicked = false;

    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application *app)
        {
            this->app = app;

            //////////////////////////////////sound//////////////////////////////////
            // Initialize SDL
            if (SDL_Init(SDL_INIT_AUDIO) < 0)
            {
                handleSDLError("SDL_Init");
            }

            // Initialize SDL_Mixer
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            {
                handleSDLError("Mix_OpenAudio");
            }

            // Load the sound
            sound = Mix_LoadWAV("assets/sounds/gun.wav");

            if (sound == nullptr)
            {
                handleSDLError("Mix_LoadWAV");
            }
            //////////////////////////////////////////////////////////////////
        }
        void handleSDLError(const std::string &message)
        {
            std::cerr << "SDL Error: " << message << " " << SDL_GetError() << std::endl;
            exit(1);
        }
        // void AudioFinishedCallback(int channel)
        // {
        //     // Add any necessary logic after the audio finishes playing
        //     // For example, clean up resources, update game state, etc.
        //     Mix_Chunk *sound = Mix_GetChunk(channel);
        //     if (sound != nullptr)
        //     {
        //         Mix_FreeChunk(sound);
        //     }

        //     // Quit SDL_mixer
        //     Mix_CloseAudio();
        //     SDL_Quit();
        // }
        bool IsSoundPlaying(Mix_Chunk *sound)
        {
            // Check if the specific sound is playing on any channel
            for (int i = 0; i < Mix_AllocateChannels(-1); ++i)
            {
                if (Mix_Playing(i) && Mix_GetChunk(i) == sound)
                {
                    return true;
                }
            }
            return false;
        }

        // This should be called every frame to see which enemies we hit
        void update(World *world, float deltaTime)
        {

            // vector to store all colliders
            std::vector<Entity *> all_enemies;

            // camera pointer
            Entity *camera = nullptr;

            // get all colliders and the player
            for (auto entity : world->getEntities())
            {
                auto collider = entity->getComponent<Collider>();
                if (collider && entity->name == "enemy")
                {
                    // adding all colliders to the vector
                    all_enemies.push_back(entity);
                }
                // get camera (player) entity
                if (entity->name == "player")
                {
                    camera = entity;
                }
            }

            if (all_enemies.size() == 0)
            {
                app->changeState("win");
            }

            // know which collider I shot
            // we run this once per click
            if (app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1) && !mouseClicked)
            {
                mouseClicked = true;

                for (auto enemy : all_enemies)
                {
                    auto enemy_position = glm::vec3(enemy->localTransform.toMat4() * glm::vec4(0, 0, -1, 0));
                    auto gun_position = glm::vec3(camera->localTransform.toMat4() * glm::vec4(0, 0, -1, 0));

                    // Calculate vector from the gun to the enemy
                    glm::vec3 gunToEnemy = enemy_position - gun_position;

                    // Calculate the normalized direction of the gun (assuming it points along the negative z-axis)
                    // glm::vec3 gunDirection = glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)); // Adjust as needed

                    // Calculate dot product between the gun's direction and vector to the enemy
                    float dotProduct = glm::dot(gun_position, glm::normalize(gunToEnemy));

                    // Check if the enemy is in front of the gun (within a certain angle threshold)
                    // Adjust the threshold as needed (in radians)
                    // std::cout << "dot product " << dotProduct << "\n";
                    if (dotProduct < 0.1f && dotProduct > -0.1f)
                    {
                        // Enemy is in front of the gun and within the 2 by 2 window
                        // Perform actions here (e.g., shoot the enemy)
                        world->markForRemoval(enemy);
                        std::cout << "ENEMY SHOT\n";
                        break;
                    }
                }

                if (!IsSoundPlaying(sound))
                {
                    if (Mix_Playing(-1) == 0)
                    { // Check if any sound is playing (optional)
                        Mix_FreeChunk(sound);
                        sound = Mix_LoadWAV("assets/sounds/gun.wav"); // Reload the sound
                        if (sound == nullptr)
                        {
                            // Handle load error
                        }
                        else
                        {
                            Mix_PlayChannel(-1, sound, 0);
                        }
                    }
                }
            }

            else if (!app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1))
            {
                mouseClicked = false;
            }
        }
        ~Gun()
        {
            // Cleanup audio resources when the Gun is destroyed
            Mix_FreeChunk(sound);
            Mix_CloseAudio();
            SDL_Quit();
        }
    };
}
