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
		const std::shared_ptr<GEngine::GEngineCoreApplication> app = GEngine::ServiceLocator::Get<GEngine::GEngineCoreApplication>();

		co_await Context::OnLoadAsync();
	}
}
