#include "OrthoCamera.h"

OrthoCamera::OrthoCamera(float height, float width)
{
    projection = glm::ortho(-(width/2.0f), width / 2.0f, height / 2.0f, -(height / 2.f), 0.01f, 1500.f);

    cameraPos = glm::vec3(0.f, 100.f, -100.f); // camera above
    cameraPosMatrix = glm::translate(
        glm::mat4(1.0f),
        cameraPos * -1.0f
    );
    WorldUp = glm::vec3(0, 1, 0);
    centerPos = glm::vec3(0, 0, 0);
    F = glm::normalize(
        centerPos - cameraPos
    );
    R = glm::normalize(
        glm::cross(F, WorldUp)
    );
    U = glm::normalize(
        glm::cross(R, F)
    );
    cameraOrientationMatrix = glm::mat4(
        glm::vec4(R, 0),
        glm::vec4(U, 0),
        glm::vec4((F * -1.0f), 0),
        glm::vec4(glm::vec3(0, 0, 0), 1)
    );
    view = glm::lookAt(cameraPos, centerPos, WorldUp);
}
