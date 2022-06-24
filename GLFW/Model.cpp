#include "Model.h"

Model::Model()
{
}

Model::Model(std::string modelPath, const char* texPath, const char* normPath, float xTranslate,
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

        if(hasNormal)
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

void Model::textureFunctions()
{
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    if(isPNG)
    {
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            img_width,
            img_height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            tex_bytes
        );
    }
    else
    {
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            img_width,
            img_height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            tex_bytes
        );
    }

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex_bytes);

    if(hasNormal)
    {
        glGenTextures(1, &norm_tex);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, norm_tex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            img_width2,
            img_height2,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            norm_bytes
        );

        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(norm_bytes);

    }
    glEnable(GL_DEPTH_TEST);
}

void Model::vertexFunctions()
{
    if (isTextured) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(GLfloat) * fullVertexData.size(),
            fullVertexData.data(),
            GL_DYNAMIC_DRAW
        );

        if(!hasNormal)
        {
            glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                8 * sizeof(GLfloat), // X,Y,Z,Norm1,Norm2,Norm3,U,V
                (void*)0
            );

            GLintptr uvPtr = 6 * sizeof(GLfloat);
            GLintptr normPtr = 3 * sizeof(GLfloat);

            glVertexAttribPointer(
                1,
                3,
                GL_FLOAT,
                GL_TRUE,
                8 * sizeof(GLfloat),
                (void*)normPtr
            );


            glVertexAttribPointer(
                2,
                2,
                GL_FLOAT,
                GL_FALSE,
                8 * sizeof(GLfloat),
                (void*)uvPtr
            );

            glEnableVertexAttribArray(2);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
        else
        {
            glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                14 * sizeof(GLfloat), // X,Y,Z,Norm1,Norm2,Norm3,U,V, Tx, Ty, Tz, Bx, By, Bz
                (void*)0
            );

            GLintptr uvPtr = 6 * sizeof(GLfloat);
            GLintptr normPtr = 3 * sizeof(GLfloat);

            GLintptr tangentPtr = 8 * sizeof(float);
            GLintptr bitangentPtr = 11 * sizeof(float);

            glVertexAttribPointer(
                1,
                3,
                GL_FLOAT,
                GL_TRUE,
                14 * sizeof(GLfloat),
                (void*)normPtr
            );

            glVertexAttribPointer(
                2,
                2,
                GL_FLOAT,
                GL_FALSE,
                14 * sizeof(GLfloat),
                (void*)uvPtr
            );

            // for tangent
            glVertexAttribPointer(
                3,
                3,
                GL_FLOAT,
                GL_FALSE,
                14 * sizeof(GLfloat),
                (void*)tangentPtr
            );

            // for bitangent
            glVertexAttribPointer(
                4,
                3,
                GL_FLOAT,
                GL_TRUE,
                14 * sizeof(GLfloat),
                (void*)bitangentPtr
            );

            glEnableVertexAttribArray(4);
            glEnableVertexAttribArray(3);
            glEnableVertexAttribArray(2);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }
    else
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER,
            sizeof(attributes.vertices) * attributes.vertices.size(),
            &attributes.vertices[0],
            GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0,
            3,
            GL_FLOAT,
            GL_FALSE,
            3 * sizeof(float),
            (void*)0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            sizeof(GLuint) * mesh_indices.size(),
            mesh_indices.data(),
            GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

void Model::updateTransform(float xTranslate, float yTranslate, float zTranslate, float scaleAmt,
                           float rotation, float xRotate, float yRotate, float zRotate)
{
    identity = glm::mat4(1.0f);
    transform = glm::translate(identity, glm::vec3(xTranslate, yTranslate, zTranslate));
    transform = glm::scale(transform, glm::vec3(scaleAmt, scaleAmt, scaleAmt));
    transform = glm::rotate(transform,
        glm::radians(rotation),
        glm::vec3(xRotate, yRotate, zRotate));

}

void Model::updateScale(float scaleAmt)
{
    transform = glm::scale(transform, glm::vec3(scaleAmt, scaleAmt, scaleAmt));

}

void Model::drawArray(GLuint shaderProgram, glm::mat4 viewMatrix, float R, float G, float B)
{
    glActiveTexture(GL_TEXTURE0);
    GLuint tex0Loc = glGetUniformLocation(shaderProgram, "tex0");
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(tex0Loc, 0);
    
    if(hasNormal)
    {
        glActiveTexture(GL_TEXTURE1);
        GLuint norm_texLoc = glGetUniformLocation(shaderProgram, "norm_tex");
        glBindTexture(GL_TEXTURE_2D, norm_tex);
        glUniform1i(norm_texLoc, 1);
    }

    transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(
        transformLoc,
        1,
        GL_FALSE,
        glm::value_ptr(transform)
    );

    GLint color_location = glGetUniformLocation(shaderProgram, "tintColor");
    float color[3] = {R, G, B};
    glUniform3fv(color_location, 1, color);
    glBindVertexArray(VAO);
 
    glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 8);

}

void Model::deleteModel()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

