#version 330 core //Version
uniform sampler2D tex0;
uniform sampler2D norm_tex;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform float ambientStr;
uniform vec3 ambientColor;

uniform vec3 cameraPos;
uniform float specStr;
uniform float specPhong;

in vec2 texCoord;
in vec3 normCoord;
in vec3 fragPos;

in mat3 TBN;

out vec4 FragColor; //Returns a Color

// Point Light
void main()
{
    vec4 pixelColor = texture(tex0, texCoord);

    if(pixelColor.a < 0.1){
        discard;
    }

    //vec3 normal = normalize(normCoord);
    vec3 normal = texture(norm_tex, texCoord).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    normal = normalize(TBN  * normal);

    vec3 lightDir = normalize(lightPos - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 ambientCol = ambientColor * ambientStr;

    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(reflectDir, viewDir), 0.1), specPhong);
    vec3 specColor = spec * specStr * lightColor; 

    // Find distance between light source and fragment position using length function to return vector distance
    float lightToObjDis = length(lightPos - fragPos);
    // Find intensity of point light
    float pointLightInt = 1.0 / pow(lightToObjDis, 2.0);

    //               r   g   b   a     Ranges from 0->1
    //FragColor = vec4(0f, 0.7f, 0f, 1f); //Sets the color of the Fragment
    FragColor = vec4(specColor + ambientCol + diffuse + pointLightInt , 1.0) * texture(tex0, texCoord);
}