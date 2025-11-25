//
// Created by guillem on 7/27/25.
//

#include "SharedContext.h"

#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Modules/CoroutinesModule.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"

namespace PacMan
{
	SharedContext::SharedContext(GEngine::GEngineCoreModules* modules)
		: Context(modules, "Shared")
	{
	}

	tokoro::Async<void> SharedContext::OnLoadAsync()
	{
		co_await Context::OnLoadAsync();
	}
}
