#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "tiny_obj_loader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

class UnlitModel
{
public:
    std::string path;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;
    tinyobj::attrib_t attributes;
    bool success;
    std::vector<GLuint> mesh_indices;
    GLuint VAO, VBO, EBO, VBO_UV;
    glm::mat4 identity;
    glm::mat4 transform;
    glm::mat4 Pprojection;
    glm::mat4 Oprojection;

    unsigned char* tex_bytes;
    GLuint texture;
    int img_width, img_height, colorChannel;

    // Position Variables
    float posX, posY, posZ;

    // Draw variables
    unsigned int transformLoc;
    unsigned int projLoc;
    unsigned int viewLoc;

public:
    UnlitModel(float height, float width, float posX, float posY, float posZ, float scale,
               float rotation, float xRotate, float yRotate, float zRotate);
    void Draw(GLuint shaderProg, bool isPerspective, glm::mat4 viewMatrix);
    void deleteModel();
};

