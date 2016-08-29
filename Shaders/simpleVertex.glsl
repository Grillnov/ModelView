# version 430 core

layout (location = 0) in vec3 VertexCoord;
layout (location = 1) in vec3 NormalCoord;
layout (location = 2) in vec3 TextureCoord;

uniform vec3 color;
uniform mat4 MVP;
const float scale = 0.007f;

smooth out vec4 vFragColor;

void main()
{
	gl_Position = MVP * vec4(VertexCoord, 1 / scale);
	vFragColor = vec4(color, 1.0f);
}