# version 430 core

layout(location = 0) in vec3 VertexCoord;
layout(location = 1) in vec3 NormalCoord;
layout(location = 2) in vec3 TextureCoord;

uniform mat4 transformMatrix;

const float scale = 0.007f;

smooth out vec2 texCoord;

void main()
{
	vec4 VertexPos4 = vec4(VertexCoord, 1 / scale);
	gl_Position = transformMatrix * VertexPos4;
	texCoord = TextureCoord.xy;
}