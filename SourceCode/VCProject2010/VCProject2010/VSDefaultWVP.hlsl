#include "VertexOut.hlsli"

cbuffer Transform : register(b0)
{
	matrix world;
	matrix view;
	matrix prj;
}

struct VertexIn
{
	float3 pos : POSITION;
	float4 color : COLOR;
	float2 texCoord : TEXCOORD;
};

VertexOut main(VertexIn vIn)
{
	VertexOut vOut;

	vOut.worldPos = mul(world,float4(vIn.pos,1.0f)).xyz;
	vOut.pos = mul(float4(vIn.pos,1.0f), world);
	vOut.pos = mul(vOut.pos, view);
	vOut.pos = mul(vOut.pos, prj);
	vOut.color = vIn.color;
	vOut.texCoord = vIn.texCoord;
	return vOut;
}
