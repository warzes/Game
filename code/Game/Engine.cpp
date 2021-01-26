#include "stdafx.h"
#include "Engine.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "GraphicsSystem.h"
//-----------------------------------------------------------------------------
Engine& GetEngine()
{
	static Engine engine;
	return engine;
}
//-----------------------------------------------------------------------------
Engine::~Engine()
{
	close();
}
//-----------------------------------------------------------------------------
bool Engine::Init(const EngineConfig& config)
{
	if (!m_window.Init(config.window))
		return false;

#if SE_PLATFORM_WINDOWS
	if (!m_renderSystem.Init(m_window.GetHWND(), config.graphics))
		return false;
#endif

	if (!GraphicsSystem::Get().Init())
		return false;

	m_isRun = true;
	return true;
}
//-----------------------------------------------------------------------------
void Engine::Update()
{
	if (m_isEnd) return;

	m_isEnd = !m_window.Broadcast();
	Mouse::Get().Update();
	Keyboard::Get().Update();
}
//-----------------------------------------------------------------------------
void Engine::BeginFrame()
{
	if (m_isEnd) return;

	if (m_window.hasWindowFocus)
		m_renderSystem.BeginFrame(m_config.window.width, m_config.window.height);
}
//-----------------------------------------------------------------------------
void Engine::EndFrame()
{
	if (m_isEnd) return;

	if (m_window.hasWindowFocus)
	{
		GraphicsSystem::Get().Draw();
		m_renderSystem.EndFrame();
	}
	else
		::WaitMessage();
}
//-----------------------------------------------------------------------------
void Engine::close()
{
	GraphicsSystem::Get().Close();
	TextureManager::Get().Clear();
	ShaderManager::Get().Clear();
	m_renderSystem.Close();
	m_window.close();
}
//-----------------------------------------------------------------------------