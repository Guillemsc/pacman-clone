//
// Created by guillem on 6/17/25.
//

#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "Component.h"

namespace GEngineCore
{
	class Camera;
}

namespace GEngineCore
{
	class CameraComponent final : public Component
	{
	public:
		explicit CameraComponent(const std::weak_ptr<Entity> &entity);

		static ComponentType GetTypeStatic() { return ComponentType::CAMERA; }
		ComponentType GetType() override { return GetTypeStatic(); }
		const char* GetTypeName() override { return "Camera"; }

		void OnEnable() override;
		void OnTick() override;
		void OnDisable() override;

	private:
		std::weak_ptr<Camera> _camera;
	};
}

#endif //CAMERACOMPONENT_H
