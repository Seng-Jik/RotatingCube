
#include "VertexOut.hlsli"


float4 main(VertexOut vOut) : SV_TARGET
{
	return vOut.color;
}
