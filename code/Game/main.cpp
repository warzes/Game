#include "stdafx.h"
#include "Engine.h"

#if SE_COMPILER_MSVC
//#   pragma comment(lib, "winmm.lib")
#endif

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
	EngineConfig config;

	Engine& engine = GetEngine();

	if (engine.Init(config))
	{
		while (!engine.IsEnd())
		{
			engine.Update();
		}
	}

	return 0;
}