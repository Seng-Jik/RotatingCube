
//float4x4 wvp;

struct VertexIn
{
	float4 pos : POSITION;
	float4 color : COLOR;
	float2 texCoord : TEXCOORD;
};

float4 main(VertexIn vIn) : SV_POSITION
{
	return vIn.pos;
	//return mul(pos,wvp);
}
