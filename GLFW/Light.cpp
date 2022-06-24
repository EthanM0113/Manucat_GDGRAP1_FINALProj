#include "Light.h"

Light::Light()
{
	lightPos = glm::vec3(-30.f, 0.f, 0);
	lightColor = glm::vec3(1.f, 1.f, 1.f);

	ambientStr = 0.1f;
	ambientColor = glm::vec3(1.f, 1.f, 1.f);

	specStr = 3.f;
	specPhong = 10.f;

}

void Light::lightUpdate(float R, float G, float B)
{
	lightColor = glm::vec3(R, G, B);
	ambientColor = glm::vec3(R, G, B);
}

void Light::draw(GLuint shaderProgram)
{
	lightPosAddress = glGetUniformLocation(shaderProgram, "lightPos");
	glUniform3fv(lightPosAddress, 1, glm::value_ptr(lightPos));

	lightColorAddress = glGetUniformLocation(shaderProgram, "lightColor");
	glUniform3fv(lightColorAddress, 1, glm::value_ptr(lightColor));

	ambientColorAddress = glGetUniformLocation(shaderProgram, "ambientColor");
	glUniform3fv(ambientColorAddress, 1, glm::value_ptr(ambientColor));

	ambientStrAddress = glGetUniformLocation(shaderProgram, "ambientStr");
	glUniform1f(ambientStrAddress, ambientStr);

	specStrAddress = glGetUniformLocation(shaderProgram, "specStr");
	glUniform1f(specStrAddress, specStr);

	specPhongAddress = glGetUniformLocation(shaderProgram, "specPhong");
	glUniform1f(specPhongAddress, specPhong);

}

