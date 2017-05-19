#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 norm;
layout (location = 2) uniform mat4 cameraMat;
layout (location = 5) in vec2 uvs;
layout (location = 8) uniform mat4 worldTrans;
out vec2 uv;
out vec3 fragLoc;
out vec3 fragNorm;
void main()
{
	uv = uvs;
	vec4 worldLoc = worldTrans * vec4(position.x, position.y, position.z, 1);
    gl_Position = cameraMat * worldLoc;
	fragLoc = vec3(worldLoc.x, worldLoc.y, worldLoc.z);
	vec4 whatFrag = inverse(transpose(worldTrans))*vec4(norm.x,norm.y,norm.z,0);
	fragNorm = vec3(whatFrag.x, whatFrag.y, whatFrag.z);
	vec4 color = vec4(1-position.y, position.x, position.x*position.y/2,1);
}