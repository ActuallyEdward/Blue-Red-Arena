#version 330

// From Vertex Shader
in vec3 vcolor;
in vec2 vpos; // Distance from local origin

// Application data
uniform sampler2D sampler0;
uniform vec3 fcolor;
uniform int light_up;

// Output color
layout(location = 0) out vec4 color;

void main()
{
	color = vec4(fcolor * vcolor, 1.0);

	float radius = distance(vec2(0.0), vpos);
	color.xyz += (0.3 - radius) * 1.5 * vec3(1.0, 1.0, 0.0);
	if (light_up == 1)
	{
		color.xyz += max((0.3 - radius), 0) * 3 * vec3(1.0, 1.0, 0.0);
	}
}