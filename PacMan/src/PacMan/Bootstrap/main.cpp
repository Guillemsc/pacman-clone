#include <memory>

#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Modules/GameModule.h"
#include "PacMan/Games/PacManGame.h"

int main()
{
    const auto app = std::make_shared<GEngine::GEngineCoreApplication>();
    app->Init();
	app->Game().lock()->LoadGame(std::make_shared<PacMan::PacManGame>());

    while (app->CanRun())
    {
        app->Tick();
    }

	app->Dispose();

    return 0;
}
