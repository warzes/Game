#pragma once

#include "Window.h"

struct EngineConfig
{
	WindowConfig window;
};
class Engine
{
	friend Engine& GetEngine();
public:
	bool Init(const EngineConfig &config);

	void Update();

	bool IsEnd() const
	{
		return m_isEnd;
	}

private:
	Engine() = default;
	Engine(const Engine&) = delete;
	Engine(Engine&&) = delete;
	Engine operator=(const Engine&) = delete;
	Engine operator=(Engine&&) = delete;
	~Engine();

	void close();

	Window m_window;
	bool m_isEnd = false;
};

Engine& GetEngine();