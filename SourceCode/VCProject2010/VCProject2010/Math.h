#pragma once
#include <DirectXMath.h>
namespace Engine
{
	namespace Math
	{
		DirectX::XMFLOAT3 operator+ (DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b)
		{
			return DirectX::XMFLOAT3
			{
				a.x + b.x,
				a.y + b.y,
				a.z + b.z
			};
		}

		DirectX::XMFLOAT3 operator* (DirectX::XMFLOAT3 a, float b)
		{
			return DirectX::XMFLOAT3
			{
				a.x * b,
				a.y * b,
				a.z * b
			};
		}

		template <typename T>
		T& operator += (T& a, T b)
		{
			a = a + b;
			return a;
		}

		template <typename T,typename U>
		T& operator *= (T& a, U b)
		{
			a = a * b;
			return a;
		}
	}
}