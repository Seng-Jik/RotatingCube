// @eddbiddulph
// By Shadertoy fizzer
// Use the mouse to rotate the view!

#include "VertexOut.hlsli"

#define EPS float2(1e-3, 0.0)

cbuffer TitleBackground
{
	float iTime;
	float2 iMouse;
	float iWdivH;
};

float3 rotateX(float a, float3 v)
{
	return float3(v.x, cos(a) * v.y + sin(a) * v.z, cos(a) * v.z - sin(a) * v.y);
}

float3 rotateY(float a, float3 v)
{
	return float3(cos(a) * v.x + sin(a) * v.z, v.y, cos(a) * v.z - sin(a) * v.x);
}

float cube(float3 p, float3 s)
{
	return length(max(float3(0.0,0.0,0.0), abs(p) - s));
}

float customCube(float3 p, float3 s)
{
	return cube(p, s) - 0.01;
}

float circular(float t)
{
	return sqrt(1.0 - t * t);
}

float processionOfCubes(float3 p)
{
	float t = -iTime * 0.2;
	p.z -= t * 2.5;
	float rad = 0.1 + cos(floor(p.z) * 10.0) * 0.07;
	p.x += cos(floor(p.z) * 2.0) * 0.3;
	p.z -= floor(p.z);
	t /= rad;
	t -= floor(t);
	float3 org = float3(0.0, circular((t - 0.5) * 1.5) * length(float2(rad, rad)), 0.5);
	return customCube(rotateX(t * 3.1415926 * 0.5, p - org), float3(rad, rad, rad));
}

float scene(float3 p)
{
	float tunnel0 = max(-p.y, length(max(float2(0.0,0.0), float2(-abs(p.z) + 2.0, max(length(p.xy) - 2.0, 0.9 - length(p.xy))))) - 0.03);
	return min(tunnel0, processionOfCubes(p));
}

float3 sceneGrad(float3 p)
{
	float d = scene(p);
	return (float3(scene(p + EPS.xyy), scene(p + EPS.yxy), scene(p + EPS.yyx)) - float3(d,d,d)) / EPS.x;
}

float3 veil(float3 p)
{
	float l = length(p);
	return float3(1.0 - smoothstep(0.0, 4.0, l), 1.0 - smoothstep(0.0, 4.0, l), 1.0 - smoothstep(0.0, 4.0, l)) * float3(1.0, 1.0, 0.75);
}

float fract(float x)
{
	return x - floor(x);
}

float3 environment(float3 ro, float3 rd)
{
	float t = -ro.y / rd.y;
	float2 tc = ro.xz + rd.xz * t;
	float3 p = float3(tc.x, 0.0, tc.y);
	float d = scene(p);

	float u = fract(dot(tc, float2(1.0,1.0)) * 20.0);
	float s = t * 2.0;
	float stripes = smoothstep(0.0, 0.1 * s, u) - smoothstep(0.5, 0.5 + 0.1 * s, u);


	float3 col = lerp(float3(0.3, 0.3, 0.6), float3(0.3, 0.3, 0.6) * 1.3, stripes);

	return veil(p) * col * lerp(0.0,
		lerp(0.9, 1.0, 1.0) *
		lerp(0.5, 1.0, sqrt(smoothstep(0.0, 0.3, d))) *
		lerp(0.5, 1.0, sqrt(smoothstep(0.0, 0.06, d))), step(0.0, t));
}

float4 main(VertexOut vOut) : SV_TARGET
{
	float2 uv = vOut.texCoord.xy * 2.0 - float2(1.0,1.0);
	uv.x *= iWdivH;
	float3 ro = float3(0.0, 0.2, 1.0), rd = float3(uv, -0.9);

	float2 angs = float2(1.0 - iMouse.y * 0.01, 1.0 - iMouse.x * 0.01);

	ro = rotateY(angs.y, ro) + float3(0.0, 0.6, 0.0);
	rd = rotateY(angs.y, rotateX(angs.x, rd));

	float4 fragColor;
	fragColor.rgb = environment(ro, rd);

	for (int i = 0; i < 100; i ++)
	{
		float d = scene(ro);

		if (abs(d) < 1e-3)
		{
			fragColor.rgb = veil(ro) * lerp(float3(0.1, 0.1, 0.4) * 0.25, float3(1.0,1.0,1.0),
				(1.0 + dot(normalize(sceneGrad(ro)), normalize(float3(0.0, 1.0, 0.4)))) * 0.5);
		}

		ro += rd * d * 0.2;
	}

	fragColor.rgb = sqrt(fragColor.rgb);
	fragColor.a = 1.0;

	return fragColor;
}


