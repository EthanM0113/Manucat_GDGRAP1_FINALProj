#version 330 core //Version Number

//the position variable has attribute position 0
//Accesses the vertex position and assigns it to aPos
layout(location = 0) in vec3 aPos; 
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 aTex; 
layout(location = 3) in vec3 m_tangent;
layout(location = 4) in vec3 m_bitangent;

out vec2 texCoord;
out vec3 normCoord;
out vec3 fragPos;

out mat3 TBN;

//Creates a Transform variable
//We'll assign the Transformation matrix here
uniform mat4 transform;

uniform mat4 projection;

uniform mat4 view;

void main()
{
    //gl_Position is predefined
    //This is the final position of the matrix when drawn
    gl_Position = projection * view * transform * //Multiply the matrix with the position
                    vec4(aPos, 1.0); // Turns our 3x1 matrix into a 4x1


    texCoord = aTex;

    mat3 modelMatrix = mat3(transpose(inverse(transform)));
    normCoord = modelMatrix * vertexNormal;
    
    vec3 T = normalize(modelMatrix * m_tangent);
    //vec3 B = normalize(modelMatrix * m_bitangent);
    vec3 N = normCoord;

    T = normalize(T-dot(T, N) * N);
    vec3 B = cross(N, T);

    TBN = mat3(T, B, N);

    fragPos = vec3(transform * vec4(aPos, 1.0));
}