#include "entity.hpp"
#include "../deserialize-utils.hpp"

#include <glm/gtx/euler_angles.hpp>

namespace our
{

    // This function computes and returns a matrix that represents this transform
    // Remember that the order of transformations is: Scaling, Rotation then Translation
    // HINT: to convert euler angles to a rotation matrix, you can use glm::yawPitchRoll
    glm::mat4 Transform::toMat4() const
    {
        // TODO: (Req 3) Write this function
        // scale matrix
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
        // rotation matrix
        glm::mat4 rotationMatrix = glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);
        // translation matrix
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);

        // compute the complete transformation matrix
        glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;

        return transformationMatrix;
    }

    // Deserializes the entity data and components from a json object
    void Transform::deserialize(const nlohmann::json &data)
    {
        position = data.value("position", position);
        rotation = glm::radians(data.value("rotation", glm::degrees(rotation)));
        scale = data.value("scale", scale); 
        
    }

}