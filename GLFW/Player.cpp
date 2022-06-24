#include "Player.h"
#include "OrthoCamera.h"
#include "PerspectiveCamera.h"

Player::Player(std::string modelPath, const char* texPath, const char* normPath, float xTranslate,
    float yTranslate, float zTranslate, float scaleAmt, float rotation, float xRotate, float yRotate, float zRotate,
    bool isTextured, float height, float width, bool isPNG, bool hasNormal)
{
    this->isTextured = isTextured;
    this->hasNormal = hasNormal;
    path = modelPath;
    success = tinyobj::LoadObj(&attributes, &shapes, &material,
        &warning, &error, path.c_str());

    for (int i = 0; i < shapes[0].mesh.indices.size(); i++)
    {
        mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
    }

    if (!hasNormal)
    {
        for (int i = 0; i < shapes[0].mesh.indices.size(); i++)
        {
            tinyobj::index_t vData = shapes[0].mesh.indices[i];

            int pos_offset = (vData.vertex_index) * 3;
            // X
            fullVertexData.push_back(
                attributes.vertices[
                    pos_offset
                ]
            );

            // Y
            fullVertexData.push_back(
                attributes.vertices[
                    pos_offset + 1
                ]
            );

            // Z
            fullVertexData.push_back(
                attributes.vertices[
                    pos_offset + 2
                ]
            );

            // Normals
            // Float 1
            fullVertexData.push_back(
                attributes.normals[
                    (vData.normal_index) * 3
                ]
            );

            // Float 2
            fullVertexData.push_back(
                attributes.normals[
                    (vData.normal_index) * 3 + 1
                ]
            );

            // Float 3
            fullVertexData.push_back(
                attributes.normals[
                    (vData.normal_index) * 3 + 2
                ]
            );

            // U 
            fullVertexData.push_back(
                attributes.texcoords[
                    vData.texcoord_index * 2
                ]
            );

            // V 
            fullVertexData.push_back(
                attributes.texcoords[
                    (vData.texcoord_index * 2) + 1
                ]
            );
        }
    }
    else if (hasNormal)
    {
        for (int i = 0; i < shapes[0].mesh.indices.size(); i += 3) {
            tinyobj::index_t vData1 = shapes[0].mesh.indices[i];
            tinyobj::index_t vData2 = shapes[0].mesh.indices[i + 1];
            tinyobj::index_t vData3 = shapes[0].mesh.indices[i + 2];

            glm::vec3 v1 = glm::vec3(
                attributes.vertices[vData1.vertex_index * 3],
                attributes.vertices[(vData1.vertex_index * 3) + 1],
                attributes.vertices[(vData1.vertex_index * 3) + 2]
            );

            glm::vec3 v2 = glm::vec3(
                attributes.vertices[vData2.vertex_index * 3],
                attributes.vertices[(vData2.vertex_index * 3) + 1],
                attributes.vertices[(vData2.vertex_index * 3) + 2]
            );

            glm::vec3 v3 = glm::vec3(
                attributes.vertices[vData3.vertex_index * 3],
                attributes.vertices[(vData3.vertex_index * 3) + 1],
                attributes.vertices[(vData3.vertex_index * 3) + 2]
            );

            glm::vec2 uv1 = glm::vec2(
                attributes.texcoords[vData1.texcoord_index * 2],
                attributes.texcoords[(vData1.texcoord_index * 2) + 1]
            );

            glm::vec2 uv2 = glm::vec2(
                attributes.texcoords[vData2.texcoord_index * 2],
                attributes.texcoords[(vData2.texcoord_index * 2) + 1]
            );

            glm::vec2 uv3 = glm::vec2(
                attributes.texcoords[vData3.texcoord_index * 2],
                attributes.texcoords[(vData3.texcoord_index * 2) + 1]
            );

            glm::vec3 deltaPos1 = v2 - v1;
            glm::vec3 deltaPos2 = v3 - v1;

            glm::vec2 deltaUV1 = uv2 - uv1;
            glm::vec2 deltaUV2 = uv3 - uv1;

            float r = 1.0f / ((deltaUV1.x * deltaUV2.y) - (deltaUV1.y * deltaUV2.x));
            glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
            glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

            tangents.push_back(tangent);
            tangents.push_back(tangent);
            tangents.push_back(tangent);

            bitangents.push_back(bitangent);
            bitangents.push_back(bitangent);
            bitangents.push_back(bitangent);
        }

        for (int i = 0; i < shapes[0].mesh.indices.size(); i++)
        {
            tinyobj::index_t vData = shapes[0].mesh.indices[i];

            int pos_offset = (vData.vertex_index) * 3;
            // X
            fullVertexData.push_back(
                attributes.vertices[
                    pos_offset
                ]
            );

            // Y
            fullVertexData.push_back(
                attributes.vertices[
                    pos_offset + 1
                ]
            );

            // Z
            fullVertexData.push_back(
                attributes.vertices[
                    pos_offset + 2
                ]
            );

            // Normals
            // Float 1
            fullVertexData.push_back(
                attributes.normals[
                    (vData.normal_index) * 3
                ]
            );

            // Float 2
            fullVertexData.push_back(
                attributes.normals[
                    (vData.normal_index) * 3 + 1
                ]
            );

            // Float 3
            fullVertexData.push_back(
                attributes.normals[
                    (vData.normal_index) * 3 + 2
                ]
            );

            // U 
            fullVertexData.push_back(
                attributes.texcoords[
                    vData.texcoord_index * 2
                ]
            );

            // V 
            fullVertexData.push_back(
                attributes.texcoords[
                    (vData.texcoord_index * 2) + 1
                ]
            );

            fullVertexData.push_back(
                tangents[i].x
            );

            fullVertexData.push_back(
                tangents[i].y
            );

            fullVertexData.push_back(
                tangents[i].z
            );

            fullVertexData.push_back(
                bitangents[i].x
            );

            fullVertexData.push_back(
                bitangents[i].y
            );

            fullVertexData.push_back(
                bitangents[i].z
            );
        }
    }

    if (isTextured) {
        stbi_set_flip_vertically_on_load(true);
        tex_bytes =
            stbi_load(texPath,
                &img_width,
                &img_height,
                &colorChannel,
                0);

        if (hasNormal)
        {
            stbi_set_flip_vertically_on_load(true);
            norm_bytes =
                stbi_load(normPath,
                    &img_width2,
                    &img_height2,
                    &colorChannel2,
                    0);
        }
    }

    // Initial position
    identity = glm::mat4(1.0f);
    transform = glm::translate(identity, glm::vec3(xTranslate, yTranslate, zTranslate));
    transform = glm::scale(transform, glm::vec3(scaleAmt, scaleAmt, scaleAmt));
    transform = glm::rotate(transform,
        glm::radians(rotation),
        glm::vec3(xRotate, yRotate, zRotate));
    pos.x = xTranslate;
    pos.y = yTranslate;
    pos.z = zTranslate;
    globalX = xTranslate;
    globalY = yTranslate;
    globalZ = zTranslate;

    // projection
    projection = glm::perspective(glm::radians(60.0f),
        height / width,
        0.f,
        100.0f);

    this->isPNG = isPNG;
}

void Player::updateInput(GLFWwindow* window, float deltaTime, bool isPerspective, OrthoCamera* Ocamera, PerspectiveCamera* Pcamera)
{
    // Movement variables
    float movementSpeed = deltaTime * 10.f;
    float OcamMoveSpeed = deltaTime * 300.f;
    float PcamMoveSpeed = 0.10f;
    float camRotation = 0.5f;
    float rotation = deltaTime * 100.0f;
    glm::vec3 radius(10.f, 10.f, 10.f);


    // When 3rd Person Cam
    if (isPerspective)
    {
        // Move Plane forward
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            transform = glm::translate(transform, glm::vec3(0, 0, movementSpeed));
        }
        // Move Plane backward
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            transform = glm::translate(transform, glm::vec3(0, 0, -movementSpeed));
        }
        // Turn Plane right
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            //transform = glm::translate(transform, glm::vec3(movementSpeed, 0, 0));
            transform = glm::rotate(transform,
                glm::radians(rotation),
                glm::vec3(0, 1, 0));
        }
        // Turn Plane left
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            //transform = glm::translate(transform, glm::vec3(-movementSpeed, 0, 0));
            transform = glm::rotate(transform,
                glm::radians(-rotation),
                glm::vec3(0, 1, 0));
        }
        // Ascend Plane
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            transform = glm::translate(transform, glm::vec3(0, movementSpeed, 0));
        }
        // Descend Plane
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            transform = glm::translate(transform, glm::vec3(0, -movementSpeed, 0));
        }
    }
    // When Top Down cam
    else
    {
        // Move Ortho Cam up
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            Ocamera->cameraPos.z -= OcamMoveSpeed;
        }
        // Move Ortho Cam down
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            Ocamera->cameraPos.z += OcamMoveSpeed;
        }
        // Move Ortho Cam right
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            Ocamera->cameraPos.x += OcamMoveSpeed;
        }
        // Move Ortho Cam left
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            Ocamera->cameraPos.x -= OcamMoveSpeed;
        }
    }
}
