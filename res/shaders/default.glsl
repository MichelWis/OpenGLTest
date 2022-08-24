#ShaderType Vertex
#version 450 core
layout(location = 0) in vec4 position;
void main() {
	gl_Position = vec4(position);
};

#ShaderType Fragment
#version 450 core
uniform ivec2 u_Resolution;
uniform float u_GameTime;
out vec4 color;

void main() {
	vec2 uv = (gl_FragCoord.xy - .5 * u_Resolution.xy) / max(u_Resolution.x, u_Resolution.y);
	
	color = vec4(uv.xy, 1, 1);
};

#ShaderType Compute
#version 450 core

uniform ivec2 u_Resolution;
uniform double u_GameTime;

void main() {

};