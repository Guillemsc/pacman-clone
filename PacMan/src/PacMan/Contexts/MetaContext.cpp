//
// Created by guillem on 7/26/25.
//

#include "MetaContext.h"

#include "ContextsStack.h"
#include "GameplayContext.h"
#include "GEngine/Components/UiShapeButtonComponent.h"
#include "GEngine/Components/UiShapeRendererComponent.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Coroutines/Coroutines.h"
#include "GEngine/Modules/CoroutinesModule.h"
#include "GEngine/Modules/EntitiesModule.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "spdlog/spdlog.h"

namespace PacMan
{
	MetaContext::MetaContext(GEngine::GEngineCoreModules* modules)
		: Context(modules, "Meta")
	{
	}

	tokoro::Async<void> MetaContext::OnLoadAsync()
	{
		const std::shared_ptr<GEngine::Entity> uiEntity2 = _scene->AddUiEntity().lock();
		uiEntity2->AddComponent<GEngine::UiShapeRendererComponent>();
		const std::shared_ptr<GEngine::UiShapeButtonComponent> button = uiEntity2->AddComponent<GEngine::UiShapeButtonComponent>().lock();

		button->OnClick().Add(std::bind(&MetaContext::WhenPlayButtonClicked, this));

		co_await Context::OnLoadAsync();
	}

	void MetaContext::OnDispose()
	{

	}

	void MetaContext::WhenPlayButtonClicked()
	{
		const std::shared_ptr<ContextsStack> contextsStack = GEngine::ServiceLocator::Get<ContextsStack>();
		if (!contextsStack) return;

		contextsStack->Pop();
		GEngine::Coroutines::Start(&ContextsStack::PushAsync, contextsStack, std::make_shared<GameplayContext>(_modules)).Forget();
	}
}
