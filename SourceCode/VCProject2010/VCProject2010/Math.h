#pragma once
#include <DirectXMath.h>
namespace Engine
{
	namespace Math
	{
		inline DirectX::XMFLOAT3 operator+ (DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b)
		{
			return DirectX::XMFLOAT3
			{
				a.x + b.x,
				a.y + b.y,
				a.z + b.z
			};
		}

		inline DirectX::XMFLOAT2 operator+ (DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b)
		{
			return DirectX::XMFLOAT2
			{
				a.x + b.x,
				a.y + b.y
			};
		}

		inline DirectX::XMFLOAT3 operator* (DirectX::XMFLOAT3 a, float b)
		{
			return DirectX::XMFLOAT3
			{
				a.x * b,
				a.y * b,
				a.z * b
			};
		}

		inline DirectX::XMFLOAT2 operator* (DirectX::XMFLOAT2 a, float b)
		{
			return DirectX::XMFLOAT2
			{
				a.x * b,
				a.y * b
			};
		}

		inline float LengthSqrt(DirectX::XMFLOAT3 x)
		{
			return x.x * x.x + x.y * x.y + x.z * x.z;
		}

		inline float LengthSqrt(DirectX::XMFLOAT2 x)
		{
			return x.x * x.x + x.y * x.y;
		}

		inline DirectX::XMFLOAT3 operator- (DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b)
		{
			return DirectX::XMFLOAT3
			{
				a.x - b.x,
				a.y - b.y,
				a.z - b.z
			};
		}

		inline DirectX::XMFLOAT2 operator- (DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b)
		{
			return DirectX::XMFLOAT2
			{
				a.x - b.x,
				a.y - b.y
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