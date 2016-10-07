# version 430 core

smooth in vec4 vFragColor;

layout (location = 0) out vec3 color;

void main()
{
	color = vFragColor.xyz;
}