#pragma once
#include "ObjectSet.h"
#include "ObjModel.h"
namespace Game
{
	namespace GamePlay
	{
		class AnswerBoard : public Engine::ObjectSet<Engine::GameObject>
		{
		private:
			Engine::Rendering::ObjModel &board_;
		public:
			AnswerBoard();
			

		};
	}
}
