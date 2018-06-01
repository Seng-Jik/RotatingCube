#include "VertexOut.hlsli"

Texture2D spTex;
SamplerState smp;

float4 main(VertexOut vIn) : SV_TARGET
{
	return spTex.Sample(smp,vIn.texCoord);
}