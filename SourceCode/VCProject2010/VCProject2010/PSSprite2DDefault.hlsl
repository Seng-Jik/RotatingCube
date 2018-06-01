#include "VertexOut.hlsli"

Texture2D spTex;
SamplerState smp;

float4 main(VertexOut vIn) : SV_TARGET
{
	float4 p = spTex.Sample(smp,vIn.texCoord);
    return p * vIn.color;
}