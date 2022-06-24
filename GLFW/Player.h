#pragma once
#include "Model.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "tiny_obj_loader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <vector>
#include "stb_image.h"

#include "OrthoCamera.h"
#include "PerspectiveCamera.h"

class Player : public Model
{
public:
    Player(std::string modelPath, const char* texPath, const char* normPath, float xTranslate,
        float yTranslate, float zTranslate, float scaleAmt, float rotation, float xRotate, float yRotate, float zRotate,
        bool isTextured, float height, float width, bool isPNG, bool hasNormal);

    void updateInput(GLFWwindow* window, float deltaTime, bool isPerspective, OrthoCamera* Ocamera, PerspectiveCamera* Pcamera);
};

