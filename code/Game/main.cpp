#include "stdafx.h"
#include "Engine.h"
#if EXAMPLE_BREAKOUT
#	include "GameBreakout.h"
#endif
#if EXAMPLE_TEST
#	include "TestGame.h"
#endif
#if GAME_MICRO_RPG
#	include "MicroRPG.h"
#endif
#if SE_COMPILER_MSVC
#   pragma comment(lib, "OpenGL32.lib")
#	if EXAMPLE_BREAKOUT
#		pragma comment(lib, "irrKlang.lib")
#		pragma comment(lib, "freetype.lib")
#	endif
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
		Engine& engine = GetEngine();

		Game game;
		if (engine.Init(game.InitConfig()))
		{
			game.Init();

			while (!engine.IsEnd())
			{
				float dt = 0.002f; // TODO:

				engine.Update();
				game.ProcessInput(dt);
				game.Update(dt);
				engine.BeginFrame();
				game.Render();
				engine.EndFrame();
			}
		}
		game.Close();
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