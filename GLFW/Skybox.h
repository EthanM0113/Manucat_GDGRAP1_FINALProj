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
#include "stb_image.h"

#include <fstream>
#include <sstream>

class Skybox
{
public:
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	unsigned int skyboxTex;
	void initialize();
	void draw(glm::mat4 view, GLuint skyboxShader, glm::mat4 projection);
};

