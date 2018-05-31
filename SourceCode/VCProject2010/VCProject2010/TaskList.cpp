#include "stdafx.h"
#include "TaskList.h"

void Engine::TaskList::Update(float deltaTime)
{
	for (auto& func : m_tasks)
	{
		func.timer -= deltaTime;
		if (func.timer <= 0)
			func.func();
	}

	auto nend = std::remove_if(m_tasks.begin(), m_tasks.end(),
		[](SecTask& task) {
		return task.timer <= 0;
	});

	m_tasks.erase(nend, m_tasks.end());
}

void Engine::TaskList::Clear()
{
	m_tasks.clear();
}

void Engine::TaskList::AddTask(std::function<void()> func, float time)
{
	m_tasks.push_back({ func,time });
}