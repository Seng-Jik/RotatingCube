#pragma once
#include <cmath>
#include "Optional.h"
namespace Engine
{
	constexpr double Mix(double smallVar, double bigVar, double x) {	//计算插值
		return x * (bigVar - smallVar) + smallVar;
	}

	inline double SlowMotion(double p) {	//对一个0~1的浮点数进行缓动处理
		return -p * p + 2 * p;
	}

	inline double SlowMotion2(double x) {	//圆形缓动
		return sqrt(1 - (x - 1)*(x - 1));
	}

	inline double SlowMotion3(double x) {
		return 1 - SlowMotion2(1 - x);	//反向圆形缓动
	}

	inline double SlowMotion4(double x) {
		return 1 - SlowMotion(1 - x);
	}

	inline double SlowMotion5(double x) {
		constexpr double PI = 3.1415926;
		return sin(PI / 2 * x);
	}

#pragma warning(disable:4244)
	template<typename T>
	class Tween
	{
	public:
		Tween();
		Tween(const T&);

		void Update(float deltaTime);
		void Run(T target, float time, int funcID = 0);
		void Stop();

		auto& Value();

		operator T() const;
		const Tween<T>& operator = (const T&);
	private:
		T m_value;
		Optional<T> m_target;
		T m_begin;
		float m_passedTime;
		float m_allTime;
		int m_funcID;
	};

	template<typename T>
	inline Tween<T>::Tween()
	{
		m_value = T{};
	}

	template<typename T>
	inline Tween<T>::Tween(const T & v)
	{
		m_value = v;
	}

	template<typename T>
	inline void Tween<T>::Update(float deltaTime)
	{
		if (m_target.Exist())
		{
			m_passedTime += deltaTime;
			if (m_passedTime >= m_allTime)
			{
				m_value = m_target.Value();
				m_target.Clear();
			}
			else
			{
				double per = m_passedTime / m_allTime;
				switch (m_funcID)
				{
				case 1:
					per = SlowMotion(per); break;
				case 2:
					per = SlowMotion2(per); break;
				case 3:
					per = SlowMotion3(per); break;
				case 4:
					per = SlowMotion4(per); break;
				case 5:
					per = SlowMotion5(per); break;
				default:
					break;
				}

				m_value = (T)(m_begin + (m_target.Value() - m_begin)*per);
			}
		}
	}
	template<typename T>
	inline void Tween<T>::Run(T target, float time, int funcID)
	{
		m_begin = m_value;
		m_target.Emplace(target);
		m_passedTime = 0;
		m_allTime = time;
		m_funcID = funcID;
	}
	template<typename T>
	inline void Tween<T>::Stop()
	{
		m_target.Clear();
	}

	template<typename T>
	inline auto & Tween<T>::Value()
	{
		return m_value;
	}

	template<typename T>
	inline Tween<T>::operator T() const
	{
		return m_value;
	}
	template<typename T>
	inline const Tween<T>& Tween<T>::operator=(const T & v)
	{
		m_target.Clear();
		m_value = v;
		return *this;
	}
}