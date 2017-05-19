#version 430
layout (location = 3) uniform vec3 lightPos;
layout (location = 4) uniform vec3 viewPos;
in vec3 fragLoc;
in vec3 fragNorm;
in vec2 uv;
uniform sampler2D myTexture;

void main()
{
	vec3 L = normalize(lightPos - fragLoc);
	vec3 N = normalize(fragNorm);
	vec3 V = normalize(viewPos - fragLoc);
	vec3 H = normalize(L + V);
	float amb = 0.03;
	float diff = max(dot(L,N), 0.0f);
	float spec = pow(max(dot(N,H), 0.0f), 16);
	float tot=((amb)+(diff)*.6+(spec)*.3)*6;
	gl_FragColor = texture(myTexture, uv) * vec4(tot,tot,tot,1);
}