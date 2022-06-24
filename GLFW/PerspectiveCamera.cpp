#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float height, float width)
{
    lastX = width / 2.0f;
    lastY = height / 2.0f;

    projection = glm::perspective(glm::radians(60.f),
        height / width,
        0.1f,
        2000.0f);

    cameraPos = glm::vec3(0, 0.f, -150.f);
    cameraPosMatrix = glm::translate(
        glm::mat4(1.0f),
        cameraPos * -1.0f
    );
    WorldUp = glm::vec3(0, 1, 0);
    centerPos = glm::vec3(0, 0, 0.f);
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

