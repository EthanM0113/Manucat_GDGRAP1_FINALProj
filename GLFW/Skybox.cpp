#include "Skybox.h"

void Skybox::initialize()
{
    /*
7--------6
/|       /|
4--------5 |
| |      | |
| 3------|-2
|/       |/
0--------1
*/
//Vertices for the cube
    float skyboxVertices[]{
        -1.f, -1.f, 1.f, //0
        1.f, -1.f, 1.f,  //1
        1.f, -1.f, -1.f, //2
        -1.f, -1.f, -1.f,//3
        -1.f, 1.f, 1.f,  //4
        1.f, 1.f, 1.f,   //5
        1.f, 1.f, -1.f,  //6
        -1.f, 1.f, -1.f  //7
    };

    //Skybox Indices
    unsigned int skyboxIndices[]{
        1,2,6,
        6,5,1,

        0,4,7,
        7,3,0,

        4,5,6,
        6,7,4,

        0,3,2,
        2,1,0,

        0,1,5,
        5,4,0,

        3,7,6,
        6,2,3
    };

    std::string facesSkybox[]{
        "Skybox/void_rt.png",
        "Skybox/void_lf.png",
        "Skybox/void_up.png",
        "Skybox/void_dn.png",
        "Skybox/void_ft.png",
        "Skybox/void_bk.png"
    };

    // Create VAO, VBO and EBO
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);

    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    // XYZ
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_INT) * 36, &skyboxIndices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenTextures(1, &skyboxTex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);
    // Skybox wont pixelate
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++) {
        int w, h, skyCChannel;
        stbi_set_flip_vertically_on_load(false);
        unsigned char* data = stbi_load(facesSkybox[i].c_str(), &w, &h, &skyCChannel, 0);
        if (data) {
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, // R, L, T, B, F, B
                0,
                GL_RGBA,
                w,
                h,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                data
            );

            stbi_image_free(data);
        }
    }
    stbi_set_flip_vertically_on_load(true);

}

void Skybox::draw(glm::mat4 view, GLuint skyboxShader, glm::mat4 projection)
{
    glm::mat4 sky_view = glm::mat4(1.f);
    // cast mat4 to mat3 to remove translation column, b4 casting back to mat4
    sky_view = glm::mat4(glm::mat3(view));

    unsigned int skyboxViewLoc = glGetUniformLocation(skyboxShader, "view");
    glUniformMatrix4fv(skyboxViewLoc,
        1,
        GL_FALSE,
        glm::value_ptr(sky_view)
    );

    unsigned int skyboxProjLoc = glGetUniformLocation(skyboxShader, "projection");
    glUniformMatrix4fv(skyboxProjLoc,
        1,
        GL_FALSE,
        glm::value_ptr(projection)
    );

    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}
