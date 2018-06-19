#pragma once
#include <DirectXMath.h>

namespace Game
{
	namespace GamePlay
	{
		enum StageName : int
		{
			Stage1 = 1,
			Stage2 = 2,
			Stage3 = 3,
			Stage4 = 4,
			Stage5 = 5,
			Stage6 = 6,
			None = -1
		};

		const struct
		{
			const char* ModelName;
			DirectX::XMFLOAT3 AnswerRotating;
			DirectX::XMFLOAT3 Scaling, CenterOffset;
			StageName NextStage;
		} Stages[] = 
		{
			{ "box",DirectX::XMFLOAT3(0,0,0),DirectX::XMFLOAT3(0,0,0),DirectX::XMFLOAT3(0,0,-20),Stage2 },
			{ "box",DirectX::XMFLOAT3(0,0,0),DirectX::XMFLOAT3(0,0,0),DirectX::XMFLOAT3(0,0,-20),Stage3 },
			{ "box",DirectX::XMFLOAT3(0,0,0),DirectX::XMFLOAT3(0,0,0),DirectX::XMFLOAT3(0,0,-20),Stage4 },
			{ "box",DirectX::XMFLOAT3(0,0,0),DirectX::XMFLOAT3(0,0,0),DirectX::XMFLOAT3(0,0,-20),Stage5 },
			{ "box",DirectX::XMFLOAT3(0,0,0),DirectX::XMFLOAT3(0,0,0),DirectX::XMFLOAT3(0,0,-20),Stage6 },
			{ "box",DirectX::XMFLOAT3(0,0,0),DirectX::XMFLOAT3(0,0,0),DirectX::XMFLOAT3(0,0,-20),None },
		};
	}
}
