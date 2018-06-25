#pragma once
#include "ObjectSet.h"
#include "ObjModel.h"
#include "Tex2D.h"
#include "StageData.h"

namespace Game
{
	namespace GamePlay
	{
		class AnswerBoard : public Engine::ObjectSet<Engine::GameObject>
		{
		private:
			Engine::Rendering::ObjModel &board_;
			Engine::Rendering::PtrTex2D answer_;
			Engine::Rendering::PtrRTView answerRtView_;

			void renderAnswerToRT(const decltype(*Stages)&);

		public:
			AnswerBoard(const decltype(*Stages)&);
			
			void FadeOut();
		};
	}
}
