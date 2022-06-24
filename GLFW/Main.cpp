#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//Classes
#include "Light.h"
#include "PerspectiveCamera.h"
#include "OrthoCamera.h"
#include "Model.h"
#include "Player.h"
#include "Shader.h"
#include "Skybox.h"
#include "UnlitModel.h"

// Inputs
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// global variables
float width = 1000.f;
float height = 1000.f;
float deltaTime;
bool isPerspective = true;
bool isPoint = true;

//camera
PerspectiveCamera* Pcamera = new PerspectiveCamera(height, width);
OrthoCamera* Ocamera = new OrthoCamera(height, width);

int main(void)
{
    GLFWwindow* window;

    Shader* shader = new Shader();

    Skybox* skybox = new Skybox();

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    // Active View
    glm::mat4 activeView;

    //Light
    Light* pointLight = new Light();
    Light* dirLight = new Light();
    float CONST_Y_LIGHTDISTANCE = 20.f;
    float CONST_Z_CAMDISTANCE = -100.f;
    float CONST_Y_CAMDISTANCE = 35.f;
    float DIR_Z_ALLOWANCE = 10.f;

    // Model
    Player* plane = new Player("3D/A-6/A-6 Intruder.obj", "3D/A-6/Body.png", "3D/A-6/Body-n.png", 470.f, -480.f, -200.f, 4.5f,
        0.f, 1.f, 0.f, 0.f, true, height, width, false, true);

    Model* debris1 = new Model("3D/debris1/Rock001.obj", "3D/debris1/RockTexture001_diffuse.png", "", 200.f, -480.f, 100.f, 300.f,
        180.f, 0.f, 1.f, 0.f, true, height, width, true, false);

    Model* debris2 = new Model("3D/debris2/uploads_files_2580748_helmet.obj", "3D/debris2/Helmet_METAL.png", "", 470.f, -150.f, 500.f, 50.f,
        180.f, 0.f, 1.f, 0.f, true, height, width, true, false);

    Model* debris3 = new Model("3D/debris3/h4_carbine.obj", "3D/debris3/storm_covenant_carbine_diffcoloured.jpg", "", -400.f, -500.f, 500.f, 2.f,
        220.f, 0.f, 1.f, 0.f, true, height, width, false, false);

    Model* debris4 = new Model("3D/debris4/Laser_Gun_Tower-(Wavefront OBJ).obj", "3D/debris4/Laser Gun Tower_color.jpg", "", 100.f, -350.f, 900.f, 2.f,
        -250.f, 0.f, 1.f, 0.f, true, height, width, false, false);

    Model* debris5 = new Model("3D/debris5/uploads_files_925190_GuardianSpear.obj", "3D/debris5/CursedStaffMap.jpg", "", -300.f, -350.f, -200.f, 0.1f,
        70.f, 1.f, 0.f, 0.f, true, height, width, false, false);

    // add debris to debrisList
    std::vector<Model*> debrisList;
    debrisList.push_back(debris1);
    debrisList.push_back(debris2);
    debrisList.push_back(debris3);
    debrisList.push_back(debris4);
    debrisList.push_back(debris5);

    // planet
    UnlitModel* planet = new UnlitModel(height, width, -470.f, -500.f, 1050.f, 400.f, 180.f, 0.f, 1.f, 0.f);

    shader->initialize();
    skybox->initialize();

    // viewport for ortho camera
    glViewport(0, 0, width, height);

    plane->textureFunctions();
    for(int i = 0; i < debrisList.size(); i++)
        debrisList[i]->textureFunctions();

    plane->vertexFunctions();
    for (int i = 0; i < debrisList.size(); i++)
        debrisList[i]->vertexFunctions();

    // For key inputs
    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
    glfwSetCursorPosCallback(window, mouse_callback);

    // last frame's timestep
    float lastTime = glfwGetTime();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();
        plane->updateInput(window, deltaTime, isPerspective, Ocamera, Pcamera);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Current Time
        GLfloat currTime = glfwGetTime();
        // How much time has passed
        deltaTime = currTime - lastTime;

        // Draw planet
        glUseProgram(shader->sphereShaderProgram);

        if(isPerspective)
            planet->Draw(shader->sphereShaderProgram, isPerspective, Pcamera->view);
        else
            planet->Draw(shader->sphereShaderProgram, isPerspective, Ocamera->view);

        if(isPoint)
            glUseProgram(shader->shaderProgram);
        else // direction light
            glUseProgram(shader->dirShaderProgram);

        // Update Camera's position && Camera Container
        Pcamera->cameraPos.x = plane->transform[3][0];
        Pcamera->cameraPos.y = plane->transform[3][1] + CONST_Y_CAMDISTANCE;
        Pcamera->cameraPos.z = plane->transform[3][2] + CONST_Z_CAMDISTANCE;

        // active view camera
        if (isPerspective)
            activeView = Pcamera->view;
        else // ortho
            activeView = Ocamera->view;

        // Update Point Light to planet position
        pointLight->lightPos.x = planet->transform[3][0];
        pointLight->lightPos.y = planet->transform[3][1];
        pointLight->lightPos.z = planet->transform[3][2];

        // Update Direction Light to front of plane
        dirLight->lightPos.x = plane->transform[3][0];
        dirLight->lightPos.y = plane->transform[3][1];
        dirLight->lightPos.z = plane->transform[3][2] + DIR_Z_ALLOWANCE;
        
        // Set Light color
        pointLight->lightUpdate(0.98f, 0.99f, 0.74f);
        dirLight->lightUpdate(1.f, 0.77f, 0.76f);

        // Locations & Draw
        if (isPerspective)
        {
            if(isPoint)
                Pcamera->shaderLocations(shader->shaderProgram);
            else
                Pcamera->shaderLocations(shader->dirShaderProgram);
        }
        else // ortho
        {
            if(isPoint)
                Ocamera->shaderLocations(shader->shaderProgram);
            else
                Ocamera->shaderLocations(shader->dirShaderProgram);
        }

        // Draw skybox
        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LEQUAL);
        glUseProgram(shader->skyboxShader);

        skybox->draw(activeView, shader->skyboxShader, Pcamera->projection);

        // Draw light and plane
        if(isPoint)
        {
            glUseProgram(shader->shaderProgram);
            pointLight->draw(shader->shaderProgram);
            plane->drawArray(shader->shaderProgram, activeView, 0.f, 0.f, 0.f);
        }
        else
        {
            glUseProgram(shader->dirShaderProgram);
            dirLight->draw(shader->dirShaderProgram);
            plane->drawArray(shader->dirShaderProgram, activeView, 0.f, 0.f, 0.f);
        }

        // Draw debris
        if(isPoint)
        {
            for (int i = 0; i < debrisList.size(); i++)
                debrisList[i]->drawArray(shader->shaderProgram, activeView, 1.f, 1.f, 1.f);
        }
        else
        {
            for (int i = 0; i < debrisList.size(); i++)
                debrisList[i]->drawArray(shader->dirShaderProgram, activeView, 1.f, 1.f, 1.f);
        }

        if (isPerspective)
            Pcamera->updateCamera();
        else
            Ocamera->updateCamera();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        // Update last time with wcurrent time
        lastTime = currTime;
    }

    plane->deleteModel();
    planet->deleteModel();
    debrisList.clear();
    delete pointLight;
    delete dirLight;
    delete Pcamera;
    delete Ocamera;

    glfwTerminate();
    return 0;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Change cam (p -> o, o -> p)
    if (key == GLFW_KEY_1)
    {
        switch (action)
        {
        case GLFW_PRESS:
            isPerspective = !isPerspective;
            break;
        }
    }
    // switch light
    if (key == GLFW_KEY_F)
    {
        switch (action)
        {
        case GLFW_PRESS:
            isPoint = !isPoint;
            break;
        }
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (isPerspective)
    {
        if (Pcamera->firstMouse) {
            Pcamera->lastX = xpos;
            Pcamera->lastY = ypos;
            Pcamera->firstMouse = false;
        }

        float xoffset = xpos - Pcamera->lastX;
        float yoffset = Pcamera->lastY - ypos;
        Pcamera->lastX = xpos;
        Pcamera->lastY = ypos;

        float sensitivity = 0.7f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        Pcamera->yaw += xoffset;
        Pcamera->pitch += yoffset;

        std::cout << "yaw: " << Pcamera->yaw << std::endl;
        std::cout << "pitch: " << Pcamera->pitch << std::endl;

        // Constrain pitch to < 90 degrees
        if (Pcamera->pitch > 89.0f)
            Pcamera->pitch = 89.0f;
        if (Pcamera->pitch < -89.0f)
            Pcamera->pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(Pcamera->yaw)) * cos(glm::radians(Pcamera->pitch));
        direction.y = sin(glm::radians(Pcamera->pitch));
        direction.z = sin(glm::radians(Pcamera->yaw)) * cos(glm::radians(Pcamera->pitch));
        Pcamera->F = glm::normalize(direction);

    }
}

/* References
1. Ship Model - https://www.cadnav.com/3d-models/model-51230.html
2. Using updateInput() - https://www.youtube.com/watch?v=uX3Iil0F51U
3. Col-major default mat4 - https://stackoverflow.com/questions/13633395/how-do-you-access-the-individual-elements-of-a-glsl-mat4
4. Perspective to ortho cam - https://stackoverflow.com/questions/41013368/setup-orthographic-projection-correctly
5. Open GL Camera Movement - https://learnopengl.com/Getting-started/Camera
6. Space Rock Model- https://www.cgtrader.com/free-3d-models/space/planet/space-rock-asteroid-glowing-blue-core-for-game-pbr
7. Knight Helmet Model - https://www.cgtrader.com/free-3d-models/character/sci-fi-character/sci-fi-knight-helmet 
8. Halo 4 Carbine Model - https://free3d.com/3d-model/halo-4-carbine-77268.html
9. Laser Gun Tower Model - https://free3d.com/3d-model/laser-gun-tower-937110.html
10. Spear Model - https://www.cgtrader.com/free-3d-models/military/melee/guardian-spear
11. Galaxy Skybox - https://www.cleanpng.com/png-space-skybox-texture-mapping-cube-mapping-night-sk-776480/https://www.eso.org/public/images/eso0932a/
12. Globe Sphere Model - https://clara.io/view/756d712b-979e-467d-98d0-0b83a242cd10#
*/