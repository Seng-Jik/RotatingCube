#include "stdafx.h"
#include "TaskList.h"

void Engine::TaskList::Update(float deltaTime)
{
	while (!m_newTasks.empty())
	{
		m_tasks.push_back(std::move(m_newTasks.front()));
		m_newTasks.pop();
	}

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
	if (time <= 0) func();
	else m_newTasks.push({ func,time });
}