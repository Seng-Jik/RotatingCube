
struct GSOutput
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float3 wpos : WORLDPOSITION;
};

cbuffer GSCB
{
	float4 eyepos;
	float lightPower;
	float alpha;
};

float4 main(GSOutput vIn) : SV_TARGET
{
	return float4(0.0f, 0.0f, 0.0f, 1.0f);
}