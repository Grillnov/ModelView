# version 430 core

smooth in vec2 texCoord;

out vec4 color;

uniform sampler2D tex;

void main()
{
	ivec2 texIndex = ivec2(texCoord.x > 0.5f ? 1 : 0, texCoord.y > 0.5f ? 1 : 0);

	//vec4 texcolor = texelFetch(tex, texIndex, 0);
	vec4 texcolor = texture(tex, texCoord);

	color = texcolor;
}