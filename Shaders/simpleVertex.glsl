# version 430 core

layout (location = 0) in vec3 VertexCoord;
layout (location = 1) in vec3 NormalCoord;
layout (location = 2) in vec3 TextureCoord;

smooth out vec4 vFragColor;

void main()
{
	gl_Position = vec4(VertexCoord, 1.0f);
	vFragColor = vec4(VertexCoord, 1.0f);
}