#version 410 core

layout(location=0) in vec3 in_Position;
uniform mat3 rotation = mat3(1,0,0, 0,1,0, 0,0,1);

void main(void)
{
	vec3 p = rotation * vec3 (in_Position.xy, 1);
	gl_Position = vec4(p.xy, 1, 1);
}

