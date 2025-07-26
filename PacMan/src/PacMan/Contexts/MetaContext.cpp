//
// Created by guillem on 7/26/25.
//

#include "MetaContext.h"

#include "ContextsStack.h"
#include "GameplayContext.h"
#include "GEngine/Components/UiShapeButtonComponent.h"
#include "GEngine/Components/UiShapeRendererComponent.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Modules/EntitiesModule.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"
#include "spdlog/spdlog.h"

namespace PacMan
{
	std::shared_ptr<GEngine::Coroutine> MetaContext::OnLoad()
	{
		const auto app = GEngine::ServiceLocator::Get<GEngine::GEngineCoreApplication>();
		if (!app) return nullptr;

		const std::shared_ptr<GEngine::EntitiesModule> entities = app->Entities().lock();

		_rootUiEntity = entities->AddUiEntity();
		_rootUiEntity.lock()->SetName("Meta Ui");

		auto uiEntity2 = entities->AddUiEntity(_rootUiEntity);
		uiEntity2.lock()->AddComponent<GEngine::UiShapeRendererComponent>();
		std::shared_ptr<GEngine::UiShapeButtonComponent> button = uiEntity2.lock()->AddComponent<GEngine::UiShapeButtonComponent>().lock();

		button->OnClick().Add(std::bind(&MetaContext::WhenPlayButtonClicked, this));

		return Context::OnLoad();
	}

	void MetaContext::OnDispose()
	{
		const auto app = GEngine::ServiceLocator::Get<GEngine::GEngineCoreApplication>();
		if (!app) return;

		const std::shared_ptr<GEngine::EntitiesModule> entities = app->Entities().lock();

		entities->RemoveEntity(_rootUiEntity);
	}

	void MetaContext::WhenPlayButtonClicked()
	{
		spdlog::info("Clicked!");

		const std::shared_ptr<ContextsStack> contextsStack = GEngine::ServiceLocator::Get<ContextsStack>();
		if (!contextsStack) return;

		contextsStack->Pop();
		contextsStack->Push(std::make_shared<GameplayContext>());
	}
}
