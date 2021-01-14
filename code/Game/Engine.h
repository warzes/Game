#pragma once

struct EngineConfig
{

};

class EngineGlobals
{
	friend class Engine;
public:
	void Init(const EngineConfig& config);
private:
	EngineGlobals() = default;
	EngineGlobals(const EngineGlobals&) = delete;
	EngineGlobals(EngineGlobals&&) = delete;
	EngineGlobals operator=(const EngineGlobals&) = delete;
	EngineGlobals operator=(EngineGlobals&&) = delete;
};

class Engine
{
	friend Engine& GetEngine();
public:
	bool Init(const EngineConfig &config);
	void Close();

	EngineGlobals& GetGlobals()
	{
		return m_globals;
	}

private:
	Engine();
	Engine(const Engine&) = delete;
	Engine(Engine&&) = delete;
	Engine operator=(const Engine&) = delete;
	Engine operator=(Engine&&) = delete;
	~Engine();

	EngineGlobals m_globals;
	struct EngineImpl* m_impl = nullptr;
};

Engine& GetEngine();