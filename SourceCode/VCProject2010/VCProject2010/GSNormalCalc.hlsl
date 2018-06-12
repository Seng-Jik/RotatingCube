
struct GSOutput
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float3 wpos : WORLDPOSITION;
};

[maxvertexcount(3)]
void main(
	triangle float4 input[3] : SV_POSITION, 
	triangle float3 inputw[3] : WORLDPOSITION,
	inout TriangleStream< GSOutput > output
)
{
	float3 tan1 = inputw[2].xyz - inputw[0].xyz;
	float3 tan2 = inputw[1].xyz - inputw[0].xyz;
	float3 norm = normalize(cross(tan1, tan2));

	for (uint i = 0; i < 3; i++)
	{
		GSOutput element;
		element.pos = input[i];
		element.normal = norm;
		element.wpos = inputw[i];
		output.Append(element);
	}
}