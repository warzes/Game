#include "stdafx.h"
#include "Engine.h"

#if SE_COMPILER_MSVC
#   pragma comment(lib, "OpenGL32.lib")
#endif

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
#if SE_DEBUG
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
#endif

	try
	{
		EngineConfig config;

		Engine& engine = GetEngine();

		if (engine.Init(config))
		{
			while (!engine.IsEnd())
			{
				engine.Update();
				engine.BeginFrame();
				engine.EndFrame();
			}
		}
	}
	catch (const std::exception& e)
	{
		std::ostringstream msg;
		msg << "Application initialization failed!" << std::endl << std::endl;
		msg << e.what();
#if SE_PLATFORM_WINDOWS
		MessageBoxA(0, msg.str().c_str(), "Error", MB_ICONERROR);
#endif
	}


	return 0;
}