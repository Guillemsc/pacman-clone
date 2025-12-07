//
// Created by guillem on 7/27/25.
//

#include "SharedContext.h"

#include "GEngine/Components/Camera2dComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Modules/EntitiesModule.h"
#include "GEngine/ServiceLocators/ServiceLocator.h"

namespace PacMan
{
	SharedContext::SharedContext(GEngine::GEngineCoreModules* modules)
		: Context(modules, "Shared")
	{
	}

	tokoro::Async<void> SharedContext::OnLoadAsync()
	{
		const std::shared_ptr<GEngine::Entity> cameraEntity = _modules->entities->AddWorldEntity().lock();
		cameraEntity->SetName("Camera");
		cameraEntity->AddComponent<GEngine::Camera2dComponent>().lock()->SetHorizontalFov(350);
		cameraEntity->GetTransform().lock()->SetPosition({0, 0, 0});

		_cameraData = std::make_unique<CameraData>();
		_cameraData->CameraEntity = cameraEntity;
		GEngine::ServiceLocator::Register(_cameraData.get());

		co_await Context::OnLoadAsync();
	}
}
