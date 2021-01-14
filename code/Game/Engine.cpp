#include "stdafx.h"
#include "Engine.h"

Engine& GetEngine()
{
	static Engine engine;
	return engine;
}

Engine::~Engine()
{
	close();
}

bool Engine::Init(const EngineConfig& config)
{
	if (!m_window.Init(config.window))
		return false;
	return true;
}

void Engine::Update()
{
	if (m_isEnd) return;

	m_isEnd = !m_window.Broadcast();
}

void Engine::close()
{
	m_window.close();
}