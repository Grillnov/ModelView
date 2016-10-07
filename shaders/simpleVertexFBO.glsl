# version 430 core

layout (location = 0) in vec3 VertexCoord;

uniform mat4 MVP;
uniform vec4 varyingcolor;
smooth out vec4 vFragColor;

void main()
{
	gl_Position = MVP * vec4(VertexCoord, 1.0f);
	vFragColor = varyingcolor;
}