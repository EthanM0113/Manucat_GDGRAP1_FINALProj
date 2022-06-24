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

class Model
{
public:
    Model();
    Model(std::string modelPath, const char* texPath, const char* normPath, float xTranslate,
        float yTranslate, float zTranslate, float scaleAmt, float rotation, float xRotate, float yRotate, float zRotate,
        bool isTextured, float height, float width, bool isPNG, bool hasNormal);
    void textureFunctions();
    void vertexFunctions();
    void updateTransform(float xTranslate, float yTranslate, float zTranslate, float scaleAmt,
                         float rotation, float xRotate, float yRotate, float zRotate);
    void updateScale(float scaleAmt);
    void drawArray(GLuint shaderProgram, glm::mat4 viewMatrix, float R, float G, float B);
    void deleteModel();
    std::string path;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;
    tinyobj::attrib_t attributes;
    bool success;
    std::vector<GLuint> mesh_indices;
    std::vector<GLfloat> fullVertexData;
    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> bitangents;
    int img_width, img_height, colorChannel;
    int img_width2, img_height2, colorChannel2;
    unsigned char* tex_bytes;
    unsigned char* norm_bytes;
    GLuint texture;
    GLuint norm_tex;
    // boolean for texture
    bool isPNG;
    GLuint VAO, VBO, EBO;
    bool isTextured;
    bool hasNormal;
    // Position Variables
    glm::vec3 pos;
    float globalX, globalY, globalZ;

    // linear transformations
    glm::mat4 identity;
    glm::mat4 transform;
    glm::mat4 projection;
    // Initial Rotation
    float initialRotation = 0.0f;

    // for rendering
    unsigned int transformLoc;
    unsigned int projLoc;
    unsigned int viewLoc;
    GLuint texLoc;

};

