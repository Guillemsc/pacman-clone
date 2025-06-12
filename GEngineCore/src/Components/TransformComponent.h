//
// Created by guillem on 6/7/25.
//

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "Component.h"
#include "ComponentType.h"
#include "raylib.h"
#include "raymath.h"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace GEngineCore
{
	class TransformComponent : public Component, public std::enable_shared_from_this<TransformComponent>
	{
		friend class EntitiesModule;

	public:
		explicit TransformComponent(const std::weak_ptr<Entity> &entity);
		~TransformComponent() override;

		static ComponentType GetTypeStatic() { return ComponentType::TRANSFORM; }
		ComponentType GetType() override { return GetTypeStatic(); }
		const char* GetTypeName() override { return "Transform"; }

		void SetPosition(const glm::vec3 &position);
		void SetLocalPosition(const glm::vec3 &position);

		void SetRotation(const glm::quat &rotation);
		void SetLocalRotation(const glm::quat &rotation);
		void SetLocalRotationEuler(const glm::vec3 &rotation);
		void SetLocalRotationEulerDegrees(const glm::vec3 &rotation);
		void SetLocalRotationEulerDegreesZ(float rotationZ);

		void SetLocalScale(const glm::vec3 &scale);

		glm::vec3 GetPosition() const;
		glm::vec2 GetPositionXY() const;
		glm::vec3 GetLocalPosition() const;

		glm::vec3 GetRotationEuler() const;
		glm::vec3 GetRotationEulerDegrees() const;
		float GetRotationEulerZ() const;
		float GetRotationEulerDegreesZ() const;
		glm::quat GetLocalRotation() const;
		glm::vec3 GetLocalRotationEuler() const;
		glm::vec3 GetLocalRotationEulerDegrees() const;
		float GetLocalRotationEulerZ() const;
		float GetLocalRotationEulerDegreesZ() const;

		glm::vec3 GetScale() const;
		glm::vec2 GetScaleXY() const;
		glm::vec3 GetLocalScale() const;

	private:
		void SetLocalPositionAsWorldPosition();
		void RecalculateLocalPosition();
		void RecalculateLocalRotation();
		void RecalculateChildrenHierarchyWorldMatrices() const;
		void ComposeLocalMatrix();
		void RecalculateWorldMatrix();

	private:
		glm::vec3 _worldPosition = glm::vec3(0);
		glm::quat _worldRotation = glm::quat();
		glm::vec3 _worldRotationEuler = glm::vec3(0);
		glm::vec3 _worldScale = glm::vec3(1);
		glm::mat4 _worldMatrix = glm::mat4(1);

		glm::vec3 _localPosition = glm::vec3(0);
		glm::quat _localRotation = glm::quat();
		glm::vec3 _localRotationEuler = glm::vec3(0);
		glm::vec3 _localScale = glm::vec3(1);
		glm::mat4 _localMatrix = glm::mat4(1);
	};
}

#endif //TRANSFORMCOMPONENT_H
