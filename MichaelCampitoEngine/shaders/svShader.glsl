#version 330 core
layout (location = 0) in vec3 position;
uniform mat4 cameraMat;
out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;


void main()
{
	
    vec4 worldLoc = vec4(position.x, position.y, position.z, 1);
    gl_Position = cameraMat*worldLoc;
    TexCoords = position;
}  