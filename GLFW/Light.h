#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "tiny_obj_loader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <vector>

class Light
{
public:
    Light();
    glm::vec3 lightPos;
    glm::vec3 lightColor;
    void draw(GLuint shaderProgram);
    void lightUpdate(float R, float G, float B);

    // Ambient Light
    float ambientStr;
    glm::vec3 ambientColor;

    // Specular Light
    float specStr;
    float specPhong;

    // For draw
    GLuint lightPosAddress;
    GLuint lightColorAddress;
    GLuint ambientColorAddress;
    GLuint ambientStrAddress;
    GLuint specStrAddress;
    GLuint specPhongAddress;
};

