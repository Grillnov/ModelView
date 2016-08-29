# version 430 core

layout (location = 0) in vec3 VertexCoord;
layout (location = 1) in vec3 NormalCoord;
layout (location = 2) in vec3 TextureCoord;

uniform mat4 transformMatrix;
uniform mat4 ModelViewMatrix;

uniform vec3 lightPosition;

const float scale = 0.007f;

smooth out vec3 vLightDir;
smooth out vec3 normal_ES;
smooth out vec2 texCoord;
smooth out vec3 tangentE;

mat3 normal_Matrix = mat3(ModelViewMatrix);
vec3 viewLightPosition = mat3(ModelViewMatrix) * lightPosition;

void main()
{
	vec4 VertexPos4 = vec4(VertexCoord, 1 / scale);
	gl_Position = transformMatrix * VertexPos4;

	normal_ES = normalize(normal_Matrix * NormalCoord);

	vec4 vPosition4 = ModelViewMatrix * VertexPos4;
	vec3 vPosition3 = vPosition4.rgb / vPosition4.a;

	vLightDir = normalize(viewLightPosition - vPosition3);
}