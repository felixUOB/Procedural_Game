#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;  

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 object_color;

// Struct to represent a light
struct Light {
    vec3 position;
    vec3 color;
};

uniform int numLights;
uniform Light lights[10]; // Support up to 10 lights

void main()
{
	vec3 norm = normalize(Normal);
    vec3 totalDiffuse = vec3(0.0);
    vec3 totalAmbient = vec3(0.0);

    float ambientStrength = 0.1;

    // Loop through each light
    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir = normalize(lights[i].position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);

		float distance = length(lights[i].position - FragPos);
		float intensity = 1.0 / (distance * distance);

        totalDiffuse += (diff * intensity) * lights[i].color;
        totalAmbient += ambientStrength * lights[i].color;
    }

    vec3 lighting = totalAmbient + totalDiffuse;


	// Sample base color from texture
    vec3 texColor = texture(texture1, TexCoord).rgb;

    // Final color is texture modulated by lighting
    vec3 finalColor = lighting * texColor;

    FragColor = vec4(finalColor, 1.0);

}