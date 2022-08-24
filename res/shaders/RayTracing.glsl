#ShaderType Vertex
#version 450 core
layout(location = 0) in vec4 position;
void main() {
	gl_Position = vec4(position);
};

#ShaderType Fragment
#version 450 core
#define MAX_DIST 999.0
uniform ivec2 u_Resolution;
uniform float u_GameTime;
uniform sampler2D u_TextureSampler;
out vec4 color;

float rand(vec2 co) {
	return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

// rpos: ray origin; rdir: unit ray direction; vmin: AABB min bounds; vmax: AABB max bounds
float rayBoxIntersect(vec3 rpos, vec3 rdir, vec3 vmin, vec3 vmax)
{
	float t1 = (vmin.x - rpos.x) / rdir.x;
	float t2 = (vmax.x - rpos.x) / rdir.x;
	float t3 = (vmin.y - rpos.y) / rdir.y;
	float t4 = (vmax.y - rpos.y) / rdir.y;
	float t5 = (vmin.z - rpos.z) / rdir.z;
	float t6 = (vmax.z - rpos.z) / rdir.z;

	float t7 = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float t8 = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));
	float t9 = (t8 < 0 || t7 > t8) ? MAX_DIST + 2 : t7;
	return t9;
}


// rpos: ray origin; rdir: unit ray direction; vmin: AABB min bounds; vmax: AABB max bounds
float rayBoxIntersectUnit(vec3 rpos, vec3 rdir, vec3 vmin)
{
	float t1 = (vmin.x - rpos.x);
	float t2 = (t1 + 1) / rdir.x;
	t1 = (t1) / rdir.x;

	float t3 = (vmin.y - rpos.y);
	float t4 = (t3 + 1) / rdir.y;
	t3 = t3 / rdir.y;

	float t5 = (vmin.z - rpos.z);
	float t6 = (t5 + 1) / rdir.z;
	t5 = t5 / rdir.z;

	float t7 = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float t8 = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));
	float t9 = (t8 < 0 || t7 > t8) ? MAX_DIST + 2 : t7;
	return t9;
}

void main() {
	//vec2 uv = (gl_FragCoord.xy / u_Resolution.x);
	vec2 uv = (gl_FragCoord.xy - .5 * u_Resolution.xy) / max(u_Resolution.x, u_Resolution.y);
	vec3 normRD = normalize(vec3(uv.xy, 1.));
	vec3 camPos = vec3(5, 5, -20);

	float idk = MAX_DIST + 1;
	vec3 boxCenter = 10. * vec3(rand(vec2(1, 9.2)), rand(vec2(5 + 0.3, 9.1)), 0);
	mediump float intersect = 0.;
	//vec3 boxCenter = 10. *  vec3(rand(vec2(i, 9.2)),rand(vec2(i + 0.3, 9.1)),0);
	for (int i = 0; i < 50000; i++) {
		intersect = rayBoxIntersectUnit(camPos, normRD, boxCenter);
		idk = min(intersect, idk);
	}
	float v = idk / MAX_DIST;
	color = vec4(v, v, v, 1);
};

#ShaderType Compute
#version 450 core
#define MAX_SPHERES 100
#define MAX_DIST 100
#define MIN_DIST 0.1

#define FOG_START .5
#define FOG_FALLOFF 0.05

#define NUM_VOXELS_BUFFER 16

#define APPLY_FOG false

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
layout(rgba32f, binding = 0) uniform image2D img_Output;

// voxel data
uniform ivec3 u_VoxelPositionBuffer[NUM_VOXELS_BUFFER];
// number of voxels
uniform int u_NVoxels;
uniform ivec2 u_Resolution;
uniform double u_GameTime;

float GetDistCube(vec3 _pos, vec3 _scale, vec3 _currPt) {
	vec3 pointRelative = _currPt - _pos;
	vec3 absPos = abs(pointRelative) - _scale;
	return max(absPos.x, max(absPos.y, absPos.z));
};

float RayMarchTrivial(vec3 _rO, vec3 _rD) {
	// basically an "unsigned byte * 2" (doesnt make any sense, but is smaller than normal int...)
	lowp int sphereCnt = 0;
	mediump float dO = 0.0;
	vec3 currentPoint = _rO;
	mediump float dS = MAX_DIST;
	while (sphereCnt < MAX_SPHERES && dO < MAX_DIST) {
		if (dS < MIN_DIST) {
			if (!APPLY_FOG) return 1;
			mediump float fog = (dO - (FOG_START * MAX_DIST)) * FOG_FALLOFF;
			return 1 - fog;
		}
		sphereCnt++;
		for (int voxel = 0; voxel < u_NVoxels; voxel++) {
			dS = min(GetDistCube(u_VoxelPositionBuffer[voxel], vec3(0.4), currentPoint), dS);
		}
		dO = dO + dS;
		currentPoint = currentPoint + dS * _rD;
	}
	return 0;
};

void main() {
	ivec2 pixelCoords = ivec2(gl_GlobalInvocationID.xy);

	vec2 pixelCoordsf = vec2(pixelCoords);
	vec2 uvs = (pixelCoordsf.xy - 0.5 * vec2(u_Resolution.xy)) / float(u_Resolution.y);
	vec3 normUVs = normalize(vec3(uvs, 1));

	float pVal = RayMarchTrivial(vec3(0, 0, -30), normUVs);
	pVal = pVal;
	imageStore(img_Output, pixelCoords, vec4(pVal, pVal, 255, 1.0));
};