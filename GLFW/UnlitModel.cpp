#include "UnlitModel.h"

// Constructor
UnlitModel::UnlitModel(float height, float width, float posX, float posY, float posZ, float scale,
                       float rotation, float xRotate, float yRotate, float zRotate)
{
    path = "3D/globe-sphere.obj";
    success = tinyobj::LoadObj(&attributes,
        &shapes,
        &material,
        &warning,
        &error,
        path.c_str());
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
    }

    // VAO, VBO and EBO
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

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Matrices
    identity = glm::mat4(1.0f);
    transform = glm::translate(identity, glm::vec3(posX, posY, posZ));
    transform = glm::scale(transform, glm::vec3(scale, scale, scale));
    transform = glm::rotate(transform,
        glm::radians(rotation),
        glm::vec3(xRotate, yRotate, zRotate));

    Pprojection = glm::perspective(glm::radians(60.f),
        height / width,
        0.1f,
        2000.0f);

     Oprojection = glm::ortho(-(width / 2.0f), width / 2.0f, height / 2.0f, -(height / 2.f), 0.1f, 1500.f);
}

void UnlitModel::Draw(GLuint shaderProg, bool isPerspective, glm::mat4 viewMatrix)
{
    transformLoc = glGetUniformLocation(shaderProg, "transform");
    glUniformMatrix4fv(transformLoc,
        1,
        GL_FALSE,
        glm::value_ptr(transform));

    if(isPerspective)
    {
        this->projLoc = glGetUniformLocation(shaderProg, "projection");
        glUniformMatrix4fv(projLoc,
            1,
            GL_FALSE,
            glm::value_ptr(Pprojection));
    }
    else
    {
        this->projLoc = glGetUniformLocation(shaderProg, "projection");
        glUniformMatrix4fv(projLoc,
            1,
            GL_FALSE,
            glm::value_ptr(Oprojection));
    }

    this->viewLoc = glGetUniformLocation(shaderProg, "view");
    glUniformMatrix4fv(viewLoc,
        1,
        GL_FALSE,
        glm::value_ptr(viewMatrix));

    glUseProgram(shaderProg);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,
        mesh_indices.size(),
        GL_UNSIGNED_INT,
        0);
}

void UnlitModel::deleteModel()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
