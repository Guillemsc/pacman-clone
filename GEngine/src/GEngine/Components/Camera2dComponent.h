//
// Created by guillem on 11/25/25.
//

#ifndef CAMERA2DCOMPONENT_H
#define CAMERA2DCOMPONENT_H

#include <memory>

#include "Component.h"

namespace GEngine
{
	class GEngineCoreModules;
	class Entity;
	class Camera2d;

	class Camera2dComponent final : public Component
	{
	public:
		explicit Camera2dComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity);

		constexpr const char* GetTypeName() override { return "Camera2d"; }

		void OnEnable() override;
		void OnTick() override;
		void OnDisable() override;

		void SetHorizontalFov(float zoom) const;

	private:
		std::weak_ptr<Camera2d> _camera;

		std::shared_ptr<Property<float>> _horizontalFovProperty;
	};
}

#endif //CAMERA2DCOMPONENT_H
