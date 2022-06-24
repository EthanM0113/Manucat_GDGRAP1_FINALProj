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


class Shader
{
public:
	GLuint shaderProgram;
	GLuint sphereShaderProgram;
	GLuint dirShaderProgram;
	GLuint skyboxShader;

public:
	void initialize();
};

