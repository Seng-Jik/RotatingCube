
struct GSOutput
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
};


float4 main(GSOutput input) : SV_TARGET
{
	return float4(input.normal.x,input.normal.y,input.normal.z,1.0f);
}