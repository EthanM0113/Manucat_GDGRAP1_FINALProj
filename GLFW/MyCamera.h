#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

class MyCamera
{
public:
    void shaderLocations(GLuint shaderProgram);
    void updateCamera();
    unsigned int projectionLoc;
    unsigned int transformLoc;
    unsigned int viewLoc;
    
    // Camera
    glm::mat4 projection;
    glm::vec3 cameraPos;
    glm::mat4 cameraPosMatrix;
    glm::vec3 WorldUp;
    glm::vec3 centerPos;
    glm::vec3 F;
    glm::vec3 R;
    glm::vec3 U;
    glm::mat4 cameraOrientationMatrix;
    glm::mat4 view;
    GLuint cameraPosAddress;

};

