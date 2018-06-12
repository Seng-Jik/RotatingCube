
struct GSOutput
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
};

[maxvertexcount(3)]
void main(
	triangle float4 input[3] : SV_POSITION, 
	inout TriangleStream< GSOutput > output
)
{
	float3 tan1 = input[2].xyz - input[0].xyz;
	float3 tan2 = input[1].xyz - input[0].xyz;
	float3 norm = normalize(cross(tan1, tan2));

	for (uint i = 0; i < 3; i++)
	{
		GSOutput element;
		element.pos = input[i];
		element.normal = norm;
		output.Append(element);
	}
}