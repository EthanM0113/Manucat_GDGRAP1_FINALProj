#include "Shader.h"

void Shader::initialize()
{
    // Vertex 
    std::fstream vertStream("Shaders/sample.vert");
    std::stringstream vertStrStream;

    vertStrStream << vertStream.rdbuf();
    std::string vertStr = vertStrStream.str();

    const char* vertSrc = vertStr.c_str();

    //Frag
    std::fstream fragStream("Shaders/sample.frag");
    std::stringstream fragStrStream;

    fragStrStream << fragStream.rdbuf();
    std::string fragStr = fragStrStream.str();

    const char* fragSrc = fragStr.c_str();

    // Direction Light Frag
    std::fstream dirFragStream("Shaders/dirFrag.frag");
    std::stringstream dirFragStrStream;

    dirFragStrStream << dirFragStream.rdbuf();
    std::string dirFragStr = dirFragStrStream.str();

    const char* dirFragSrc = dirFragStr.c_str();

    // Sphere Vertex 
    std::fstream sphereVertStream("Shaders/sphereVert.vert");
    std::stringstream sphereVertStrStream;

    sphereVertStrStream << sphereVertStream.rdbuf();
    std::string sphereVertStr = sphereVertStrStream.str();

    const char* sphereVertSrc = sphereVertStr.c_str();

    //Sphere Frag
    std::fstream sphereFragStream("Shaders/sphereFrag.frag");
    std::stringstream sphereFragStrStream;

    sphereFragStrStream << sphereFragStream.rdbuf();
    std::string sphereFragStr = sphereFragStrStream.str();

    const char* sphereFragSrc = sphereFragStr.c_str();

    //Skybox Vertex 
    std::fstream skyboxVertStream("Shaders/skybox.vert");
    std::stringstream skyboxVertStrStream;

    skyboxVertStrStream << skyboxVertStream.rdbuf();
    std::string skyboxVertStr = skyboxVertStrStream.str();

    const char* skyboxVertSrc = skyboxVertStr.c_str();

    //Skybox Frag 
    std::fstream skyboxFragStream("Shaders/skybox.frag");
    std::stringstream skyboxFragStrStream;

    skyboxFragStrStream << skyboxFragStream.rdbuf();
    std::string skyboxFragStr = skyboxFragStrStream.str();

    const char* skyboxFragSrc = skyboxFragStr.c_str();

    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertSrc, NULL);
    glCompileShader(vertShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSrc, NULL);
    glCompileShader(fragShader);

    GLuint dirFragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dirFragShader, 1, &dirFragSrc, NULL);
    glCompileShader(dirFragShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);

    dirShaderProgram = glCreateProgram();
    glAttachShader(dirShaderProgram, vertShader);
    glAttachShader(dirShaderProgram, dirFragShader);
    glLinkProgram(dirShaderProgram);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    glDeleteShader(dirFragShader);

    // Sphere shader
    GLuint sphereVertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sphereVertShader, 1, &sphereVertSrc, NULL);
    glCompileShader(sphereVertShader);

    GLuint sphereFragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sphereFragShader, 1, &sphereFragSrc, NULL);
    glCompileShader(sphereFragShader);

    sphereShaderProgram = glCreateProgram();
    glAttachShader(sphereShaderProgram, sphereVertShader);
    glAttachShader(sphereShaderProgram, sphereFragShader);

    glLinkProgram(sphereShaderProgram);
    glDeleteShader(sphereVertShader);
    glDeleteShader(sphereFragShader);

    // Skybox shader
    GLuint skyboxVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(skyboxVertexShader, 1, &skyboxVertSrc, NULL);
    glCompileShader(skyboxVertexShader);

    GLuint skyboxFragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(skyboxFragShader, 1, &skyboxFragSrc, NULL);
    glCompileShader(skyboxFragShader);

    skyboxShader = glCreateProgram();
    glAttachShader(skyboxShader, skyboxVertexShader);
    glAttachShader(skyboxShader, skyboxFragShader);

    glLinkProgram(skyboxShader);
    glDeleteShader(skyboxVertexShader);
    glDeleteShader(skyboxFragShader);

}

