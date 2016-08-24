//!Shader!
//!VertexShader!
# version 430 core
layout (location = 0) in vec4 attr_vertex;
layout (location = 1) in vec3 attr_normal;
layout (location = 2) in vec2 attr_texCoord;
layout (location = 3) in int ID;
layout (location = 4) in vec3 attr_tangent;

uniform mat4 transformMatrix;
uniform mat4 ModelViewMatrix;

uniform vec3 lightPosition;

smooth out vec3 vLightDir;
smooth out vec3 normal_ES;
smooth out vec2 texCoord;
smooth out vec3 tangentE;

mat3 normal_Matrix = mat3(ModelViewMatrix);
vec3 viewLightPosition = mat3(ModelViewMatrix) * lightPosition;

void main()
{
	gl_Position = transformMatrix * vec4(attr_vertex.xyz, 1.0f);

	normal_ES = normalize(normal_Matrix * attr_normal);

	vec4 vPosition4 = ModelViewMatrix * attr_vertex;
	vec3 vPosition3 = vPosition4.rgb / vPosition4.a;

	vLightDir = normalize(viewLightPosition - vPosition3);

	texCoord = attr_texCoord;

	tangentE = mat3(ModelViewMatrix) * normalize(attr_tangent);
}

//!VertexShaderEnd!

//!FragmentShader!
#version 430 core

smooth in vec3 vLightDir;
smooth in vec3 normal_ES;
smooth in vec2 texCoord;
smooth in vec3 tangentE;

out vec4 color;

uniform sampler2D tex;
uniform sampler2D texNorm;

uniform vec4 lightColor;
uniform vec4 diffuseColor;
uniform vec4 ambientColor;

void main()
{
	vec3 BitangentE = cross(normal_ES, tangentE);
	vec3 BumpMapNormal = texture(texNorm, texCoord).xyz;
	BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);                              
    vec3 NewNormal;                                                                         
    mat3 TBN = mat3(tangentE, BitangentE, normal_ES);                                            
    NewNormal = TBN * BumpMapNormal;                                                        
    NewNormal = normalize(NewNormal);                                     

	vec4 diffuse, specular, ambient;
	vec3 normal = normalize(NewNormal);
	float diff = max(0.0, dot(normal, vLightDir));
	diffuse = diff * diffuseColor;

	vec3 reflectionv = reflect(-vLightDir, normal);
	float reflectAngle = max(0.0, dot(normal, normalize(reflectionv)));
	float specFactor = pow(reflectAngle, 128);
	specular = specFactor * lightColor;

	vec4 vVaryingColor = specular + diffuse + ambientColor;
	color = vVaryingColor * texture(tex, texCoord);
}

//!FragmentShaderEnd!