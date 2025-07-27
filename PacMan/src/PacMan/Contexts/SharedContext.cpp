//
// Created by guillem on 7/27/25.
//

#include "SharedContext.h"

#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Modules/CoroutinesModule.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"

namespace PacMan
{
	SharedContext::SharedContext() : Context("Shared")
	{
	}

	tokoro::Async<void> SharedContext::OnLoadAsync()
	{
		const auto app = GEngine::ServiceLocator::Get<GEngine::GEngineCoreApplication>();
		if (!app) co_return;

		//const std::shared_ptr<GEngine::CoroutinesModule> coroutines = app->Coroutines().lock();

		//patrolTask = coroutines->Scheduler().Start(&SharedContext::awkwardHello, this, "what", 1);

		co_await Context::OnLoadAsync();
	}
}
