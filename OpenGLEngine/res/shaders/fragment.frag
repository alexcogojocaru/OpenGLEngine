#version 330 core

in vec3 outColor;

out vec4 color;

uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

void main()
{
//	color = mix(texture(u_texture1, outTexture), texture(u_texture2, outTexture), 0.2);
	color = vec4(outColor, 1.0);
}