#pragma once
#include "Sprite2D.h"
#include "ObjectSet.h"
namespace Game
{
	namespace GamePlay
	{
		class Clock : public Engine::ObjectSet<Engine::Rendering::Sprite2D>
		{
		private:
			Engine::Rendering::Sprite2D
				&m1_, &min1_, &min2_, &sec1_, &sec2_;// , &ms1_, &ms2_;

			Engine::Tween<float> zoom_ = 1, x_ = 0, y_ = 0,alpha_ = 1;

			static void setDisplay(Engine::Rendering::Sprite2D& display, int num);
			static void setNumDisplay(
				Engine::Rendering::Sprite2D& b1,
				Engine::Rendering::Sprite2D& b2,
				int num);

			float sec_ = 0;
		public:
			Clock();
			void Update(float d) override;

			void SetPos(float x, float y,float tween = -1);
			void SetZoom(float zoom, float tween = -1);

			void SetTime(float sec);
			inline float GetTime() const
			{
				return sec_;
			}

			inline auto& Alpha()
			{
				return alpha_;
			}
		};
	}
}