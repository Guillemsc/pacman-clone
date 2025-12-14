#include <memory>

#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Memory/MemoryTracker.h"
#include "GEngine/Modules/GameModule.h"
#include "PacMan/Games/PacManGame.h"
#include "PacMan/Contexts/ContextsStack.h"

int main()
{
	// Main entry point.
	// Initializes the core engine, loads the PacMan game, and runs the main loop.

	{
		const auto app = std::make_shared<GEngine::GEngineCoreApplication>();
		app->Init();
		app->Modules()->game->LoadGame(std::make_shared<PacMan::PacManGame>());

		while (app->CanRun())
		{
			app->Tick();
		}

		app->Dispose();
	}

    return 0;
}
