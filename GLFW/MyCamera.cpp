#include "MyCamera.h"

void MyCamera::shaderLocations(GLuint shaderProgram)
{
    transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(
        transformLoc,
        1,
        GL_FALSE,
        glm::value_ptr(cameraPosMatrix)
    );

    viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(
        viewLoc,
        1,
        GL_FALSE,
        glm::value_ptr(view)
    );

    cameraPosAddress = glGetUniformLocation(shaderProgram, "cameraPos");
    glUniform3fv(cameraPosAddress, 1, glm::value_ptr(cameraPos));

    projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(
        projectionLoc,
        1,
        GL_FALSE,
        glm::value_ptr(projection)
    );
    
}

void MyCamera::updateCamera()
{
    view = glm::lookAt(cameraPos, cameraPos + F, U);
}
