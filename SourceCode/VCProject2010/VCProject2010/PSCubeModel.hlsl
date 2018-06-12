
struct GSOutput
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float3 wpos : WORLDPOSITION;
};

cbuffer GSCB
{
	float4 eyepos;
};

struct Light
{
	float3 pos;
};

float Lambert(
	float3 normal,
	float3 lightDirection)
{
	return
		max(
			0.0f,
			dot(
				normalize(normal),
				normalize(lightDirection)));
}

float BlinPhong(
	float3 normal,
	float3 lightDirection,
	float3 viewDirection,
	float specPower)
{
	float diff = Lambert(normal, lightDirection);
	float3 halfVector = normalize(lightDirection + viewDirection);
	float spec = pow(
		max(
			0.0f,
			dot(
				halfVector,
				normalize(normal)))
		, specPower);

	return diff + spec;
}

float Lighting(Light light, float3 normal, float3 wpos)
{
	float l = BlinPhong(normal, light.pos - wpos, eyepos - wpos, 70.0f);
	return l * 0.5f + 0.25f;
}

float4 main(GSOutput input) : SV_TARGET
{
	//这里有个魔法光源
	Light light;
	light.pos.x = 50.0f;
	light.pos.y = -50.0f;
	light.pos.z = -10.0f;

	float rgb = Lighting(light, input.normal, input.wpos);

	return float4(rgb,rgb,rgb,1.0f);
}