#include "VertexOut.hlsli"


struct VertexIn
{
	float3 pos : POSITION;
	float4 color : COLOR;
	float2 texCoord : TEXCOORD;
};

VertexOut main(VertexIn vIn)
{
	VertexOut vOut;
	vOut.pos = float4(vIn.pos,1.0f);
	vOut.color = vIn.color;
	vOut.texCoord = vIn.texCoord;
	return vOut;
}
