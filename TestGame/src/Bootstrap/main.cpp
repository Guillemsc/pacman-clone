#include <memory>

#include "Core/GEngineCoreApplication.h"
#include "Modules/GameModule.h"
#include "../Games/TestGame.h"

int main()
{
    const auto app = std::make_shared<GEngineCore::GEngineCoreApplication>();
    app->Init();
	app->Game().lock()->LoadGame(std::make_shared<TestGame>());

    while (app->CanRun())
    {
        app->Tick();
    }

     app->Dispose();

    return 0;
}
