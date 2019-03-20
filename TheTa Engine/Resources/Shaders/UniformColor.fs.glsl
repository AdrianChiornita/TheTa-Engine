#version 330

in vec3 frag_normal;
in vec2 tex_coord;

uniform vec3 color;

layout(location = 0) out vec4 out_color;

void main()
{
	out_color = vec4(abs(color), 1);
}