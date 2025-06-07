#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;  

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 object_color;
uniform vec3 lightSource_color;

uniform vec3 lightSource_position;

void main()
{
	// diffuse lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightSource_position - FragPos); 

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightSource_color;

	// ambient lighting
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightSource_color;

	vec3 lighting = ambient + diffuse;


	 // Sample base color from texture
    vec3 texColor = texture(texture1, TexCoord).rgb;

    // Final color is texture modulated by lighting
    vec3 finalColor = lighting * texColor;

    FragColor = vec4(finalColor, 1.0); // Use 1.0 for opaque alpha

}