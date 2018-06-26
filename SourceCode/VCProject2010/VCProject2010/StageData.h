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
			StageName Current;
			DirectX::XMFLOAT3 AnswerRotating;
			float Scaling;
			DirectX::XMFLOAT3 CenterOffset;
			StageName NextStage;
			DirectX::XMFLOAT3 InitRotating;
		} Stages[] = 
		{
			{ 
				"Stage1",
				Stage1,
				DirectX::XMFLOAT3(67.7283f,70.6874f,0),
				0.5f,
				DirectX::XMFLOAT3(0,-20,-40),
				Stage2,
				DirectX::XMFLOAT3(3.11155f,4.69016f,0) 
			},

			{ 
				"Stage2",
				Stage2,
				DirectX::XMFLOAT3(4.09919f,5.65187f,0),
				0.2F,
				DirectX::XMFLOAT3(0,0,-60),
				Stage3,
				DirectX::XMFLOAT3(0.283272F,2.48313F,0) 
			},

			{ 
				"Stage3",
				Stage3,
				DirectX::XMFLOAT3(5.38447f,5.8888f,0),
				0.3F,
				DirectX::XMFLOAT3(0,0,-40),
				Stage4,
				DirectX::XMFLOAT3(2.31875f,3.02431f,0)
			},

			{ "box",Stage4,DirectX::XMFLOAT3(0,0,0),1,DirectX::XMFLOAT3(0,0,-20),Stage5,DirectX::XMFLOAT3(0,0,0) },
			{ "box",Stage5,DirectX::XMFLOAT3(0,0,0),1,DirectX::XMFLOAT3(0,0,-20),Stage6,DirectX::XMFLOAT3(0,0,0) },
			{ "box",Stage6,DirectX::XMFLOAT3(0,0,0),1,DirectX::XMFLOAT3(0,0,-20),None,DirectX::XMFLOAT3(0,0,0) },
		};
	}
}
