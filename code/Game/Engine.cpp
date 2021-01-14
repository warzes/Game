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

#if SE_PLATFORM_WINDOWS
	if (!m_graphics.Init(m_window.GetHWND(), config.window, config.graphics))
		return false;
#endif
	return true;
}

void Engine::Update()
{
	if (m_isEnd) return;

	m_isEnd = !m_window.Broadcast();
}

void Engine::BeginFrame()
{
	if (m_isEnd) return;

	if (m_window.hasWindowFocus)
		m_graphics.BeginFrame();
}

void Engine::EndFrame()
{
	if (m_isEnd) return;

	if (m_window.hasWindowFocus)
		m_graphics.EndFrame();
	else
		::WaitMessage();
}

void Engine::close()
{
	m_graphics.close();
	m_window.close();
}