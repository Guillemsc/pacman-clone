//
// Created by guillem on 6/17/25.
//

#include "CameraComponent.h"

#include "TransformComponent.h"
#include "Cameras/Camera.h"
#include "Modules/CameraModule.h"

namespace GEngineCore
{
	CameraComponent::CameraComponent(const std::weak_ptr<Entity> &entity): Component(entity)
	{
	}

	void CameraComponent::OnEnable()
	{
		const std::shared_ptr<GEngineCoreApplication> app = GetApp().lock();
		if (!app) return;

		const std::shared_ptr<CameraModule> camera = app->Camera().lock();
		if (!camera) return;

		_camera = camera->CreateCamera();
	}

	void CameraComponent::OnTick()
	{
		const std::shared_ptr<Camera> camera = _camera.lock();
		if (!camera) return;

		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return;

		const std::shared_ptr<TransformComponent> transform = entity->GetTransform().lock();
		if (!entity) return;

		const glm::vec3 position = transform->GetPosition();
		const glm::quat rotation = transform->GetRotation();

		camera->SetPosition(position);
		camera->SetRotation(rotation);
	}

	void CameraComponent::OnDisable()
	{
		const std::shared_ptr<GEngineCoreApplication> app = GetApp().lock();
		if (!app) return;

		const std::shared_ptr<CameraModule> camera = app->Camera().lock();
		if (!camera) return;

		camera->RemoveCamera(_camera);
		_camera.reset();
	}
} // GEngineCore