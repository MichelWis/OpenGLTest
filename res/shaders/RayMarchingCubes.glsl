#ShaderType Vertex
#version 450 core
layout(location = 0) in vec4 position;
void main() {
	gl_Position = vec4(position);
};

#ShaderType Fragment
#version 450 core
#define MAX_SPHERES 75
#define MAX_DISTANCE 75.
#define HIT_DISTANCE .025
#define FOG_START .01
#define FOG_FALLOFF 0.1

uniform ivec2 u_Resolution;
// game time in seconds.
uniform float u_GameTime;
uniform vec2 u_CameraRotation;
uniform vec3 u_CameraPosition;
uniform isampler1D u_VoxelSampler;
uniform int u_VoxelCount;
out vec4 color;

float RayMarch(vec3 _ro, vec3 _rd) {
	float distOrigin = 0.;

	for (int i = 0; i < MAX_SPHERES; i++) {
		vec3 currentPoint = _ro + distOrigin * _rd;

		float distScene = MAX_DISTANCE + 1;
		
		for (int j = 0; j < u_VoxelCount; ++j) {
			vec3 texVal = texelFetch(u_VoxelSampler, j, 0).xyz;
			
			vec3 pointRelative = currentPoint - texVal;
			vec3 absPos = abs(pointRelative);
			float tmp = max(absPos.x, max(absPos.y, absPos.z)) - 0.01;

			distScene = min(distScene, tmp);
		}

		distOrigin += distScene;
		if (distOrigin > MAX_DISTANCE || distScene < HIT_DISTANCE) break;
	}
	if (distOrigin < MAX_DISTANCE) {
		return 1;
		float fog = (distOrigin - (MAX_DISTANCE * FOG_START)) * FOG_FALLOFF;
		fog = fog * fog;
		return 1 - fog;
	}
	return 0;
};


vec4 QuatFromAxisAngle(vec3 _axis, float _angle)
{
	vec4 qr;
	float half_angle = _angle * 0.5;
	qr.x = _axis.x * sin(half_angle);
	qr.y = _axis.y * sin(half_angle);
	qr.z = _axis.z * sin(half_angle);
	qr.w = cos(half_angle);
	return qr;
}

vec4 QuatConj(vec4 _q)
{
	return vec4(-_q.x, -_q.y, -_q.z, _q.w);
}

vec4 QuatMult(vec4 _q1, vec4 _q2)
{
	vec4 qr;
	qr.x = (_q1.w * _q2.x) + (_q1.x * _q2.w) + (_q1.y * _q2.z) - (_q1.z * _q2.y);
	qr.y = (_q1.w * _q2.y) - (_q1.x * _q2.z) + (_q1.y * _q2.w) + (_q1.z * _q2.x);
	qr.z = (_q1.w * _q2.z) + (_q1.x * _q2.y) - (_q1.y * _q2.x) + (_q1.z * _q2.w);
	qr.w = (_q1.w * _q2.w) - (_q1.x * _q2.x) - (_q1.y * _q2.y) - (_q1.z * _q2.z);
	return qr;
}

vec3 RotateVertexPosition(vec3 position, vec3 axis, float angle)
{
	vec4 qr = QuatFromAxisAngle(axis, angle);
	vec4 qr_conj = QuatConj(qr);
	vec4 q_pos = vec4(position.x, position.y, position.z, 0);

	vec4 q_tmp = QuatMult(qr, q_pos);
	qr = QuatMult(q_tmp, qr_conj);

	return vec3(qr.x, qr.y, qr.z); 
};

void main() {
	vec2 uv = 1.*(gl_FragCoord.xy-.5*u_Resolution.xy) / max(u_Resolution.x, u_Resolution.y);
	
	vec3 ro = vec3(0, 0, -20);
	vec3 rd = normalize(vec3(uv.x, uv.y, 1));
		
	float distance = RayMarch(ro, rd);
	vec3 rawColor = vec3(0.4, 0.2, distance);
	color = vec4(rawColor, 1.0);
};