#pragma once
#include <functional>
#include <vector>
#include <queue>
namespace Engine
{
	class TaskList
	{
	public:
		void Update(float deltaTime);
		void Clear();
		void AddTask(std::function<void()> func, float time);
	private:
		struct SecTask
		{
			std::function<void()> func;
			float timer;
		};

		std::vector<SecTask> m_tasks;
		std::queue<SecTask> m_newTasks;
	};
}