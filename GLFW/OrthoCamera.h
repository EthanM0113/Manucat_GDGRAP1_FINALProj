#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include "MyCamera.h"

class OrthoCamera :
	public MyCamera
{
public:
	OrthoCamera(float height, float width);

};

