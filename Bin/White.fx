
cbuffer Constants
{
	float4x4 wvp;
};

struct VertexIn
{
	float4 pos : SV_POSITION;
};

struct VertexOut
{
	float4 pos : SV_POSITION;
};

VertexOut VS(VertexIn vIn)
{
	VertexOut vOut;
	vOut.pos = mul(vIn.pos, wvp);
}

float4 PS(VertexOut pIn) : SV_Target
{
	return float4(1,1,1,1);
}

technique11 Basic
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}

