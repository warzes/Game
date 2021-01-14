#include "stdafx.h"
#include "Engine.h"

Engine& GetEngine()
{
	static Engine engine;
	return engine;
}

struct EngineImpl
{
};

void EngineGlobals::Init(const EngineConfig& config)
{
}

Engine::Engine() : m_impl(new EngineImpl())
{
}

Engine::~Engine()
{
	delete m_impl;
}

bool Engine::Init(const EngineConfig& config)
{
	m_globals.Init(config);
	return true;
}

void Engine::Close()
{
}