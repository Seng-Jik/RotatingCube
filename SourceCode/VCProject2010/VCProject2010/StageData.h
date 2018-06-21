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
			float Scaling;
			DirectX::XMFLOAT3 CenterOffset;
			StageName NextStage;
			DirectX::XMFLOAT3 InitRotating;
		} Stages[] = 
		{
			{ "Stage1",DirectX::XMFLOAT3(0,0,0),0.5f,DirectX::XMFLOAT3(0,-20,-40),Stage2,DirectX::XMFLOAT3(70,50,0) },
			{ "box",DirectX::XMFLOAT3(0,0,0),1,DirectX::XMFLOAT3(0,0,-20),Stage3,DirectX::XMFLOAT3(0,0,0) },
			{ "box",DirectX::XMFLOAT3(0,0,0),1,DirectX::XMFLOAT3(0,0,-20),Stage4,DirectX::XMFLOAT3(0,0,0) },
			{ "box",DirectX::XMFLOAT3(0,0,0),1,DirectX::XMFLOAT3(0,0,-20),Stage5,DirectX::XMFLOAT3(0,0,0) },
			{ "box",DirectX::XMFLOAT3(0,0,0),1,DirectX::XMFLOAT3(0,0,-20),Stage6,DirectX::XMFLOAT3(0,0,0) },
			{ "box",DirectX::XMFLOAT3(0,0,0),1,DirectX::XMFLOAT3(0,0,-20),None,DirectX::XMFLOAT3(0,0,0) },
		};
	}
}
