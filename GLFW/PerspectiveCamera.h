#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include "MyCamera.h"

class PerspectiveCamera :
	public MyCamera
{
public:
	PerspectiveCamera(float height, float width);

	// camera direction
	float lastX;
	float lastY;
	float pitch;
	float yaw = -90.f;
	bool firstMouse = true;
};

