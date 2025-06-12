//
// Created by guillem on 6/7/25.
//

#define GLM_ENABLE_EXPERIMENTAL

#include "TransformComponent.h"

#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/quaternion.hpp"

namespace GEngineCore
{
	TransformComponent::TransformComponent(const std::weak_ptr<Entity> &entity) : Component(entity)
	{

	}

	TransformComponent::~TransformComponent()
	{
	}

	void TransformComponent::SetPosition(const glm::vec3 &position)
	{
		if (_worldPosition == position)
		{
			return;
		}

		_worldPosition = position;

		RecalculateLocalPosition();
		ComposeLocalMatrix();
		RecalculateChildrenHierarchyWorldMatrices();
	}

	void TransformComponent::SetLocalPosition(const glm::vec3 &position)
	{
		if (_localPosition == position)
		{
			return;
		}

		_localPosition = position;

		const std::shared_ptr<TransformComponent> thisShared = shared_from_this();

		ComposeLocalMatrix();
		RecalculateChildrenHierarchyWorldMatrices();
	}

	void TransformComponent::SetRotation(const glm::quat &rotation)
	{
		if (_worldRotation == rotation)
		{
			return;
		}

		_worldRotation = rotation;

		RecalculateLocalRotation();
		ComposeLocalMatrix();
		RecalculateChildrenHierarchyWorldMatrices();
	}

	void TransformComponent::SetLocalRotation(const glm::quat &rotation)
	{
		if (_localRotation == rotation)
		{
			return;
		}

		_localRotation = rotation;

		ComposeLocalMatrix();
		RecalculateChildrenHierarchyWorldMatrices();
	}

	void TransformComponent::SetLocalRotationEuler(const glm::vec3 &rotation)
	{
		const std::shared_ptr<GEngineCoreApplication> app = GetApp().lock();
		if (app == nullptr) return;

		if (_localRotationEuler == rotation)
		{
			return;
		}

		_localRotationEuler = rotation;

		const glm::quat quaternion = glm::quat(_localRotationEuler);
		SetLocalRotation(quaternion);
	}

	void TransformComponent::SetLocalRotationEulerDegrees(const glm::vec3 &rotation)
	{
		const glm::vec3 rotationRadians = glm::radians(rotation);
		SetLocalRotationEuler(rotationRadians);
	}

	void TransformComponent::SetLocalRotationEulerDegreesZ(const float rotationZ)
	{
		const float rotationRadiansZ = rotationZ * DEG2RAD;
		const glm::vec3 rotationRadians = glm::vec3(_localRotationEuler.x, _localRotationEuler.y, rotationRadiansZ);
		SetLocalRotationEuler(rotationRadians);
	}

	void TransformComponent::SetLocalScale(const glm::vec3 &scale)
	{
		const glm::vec3 clampedScale = glm::max(scale, glm::vec3(0));

		if (_localScale == clampedScale)
		{
			return;
		}

		_localScale = clampedScale;

		ComposeLocalMatrix();
		RecalculateChildrenHierarchyWorldMatrices();
	}

	glm::vec3 TransformComponent::GetPosition() const
	{
		return _worldPosition;
	}

	glm::vec2 TransformComponent::GetPositionXY() const
	{
		return {_worldPosition.x, _worldPosition.y};
	}

	glm::vec3 TransformComponent::GetLocalPosition() const
	{
		return _localPosition;
	}

	glm::vec3 TransformComponent::GetRotationEuler() const
	{
		return _worldRotationEuler;
	}

	glm::vec3 TransformComponent::GetRotationEulerDegrees() const
	{
		return glm::degrees(_worldRotationEuler);
	}

	glm::quat TransformComponent::GetLocalRotation() const
	{
		return _localRotation;
	}

	glm::vec3 TransformComponent::GetLocalRotationEuler() const
	{
		return _localRotationEuler;
	}

	glm::vec3 TransformComponent::GetLocalRotationEulerDegrees() const
	{
		return glm::degrees(_localRotationEuler);
	}

	float TransformComponent::GetRotationEulerZ() const
	{
		return _worldRotationEuler.z;
	}

	float TransformComponent::GetRotationEulerDegreesZ() const
	{
		return glm::degrees(_worldRotationEuler.z);
	}

	float TransformComponent::GetLocalRotationEulerZ() const
	{
		return _localRotationEuler.z;
	}

	float TransformComponent::GetLocalRotationEulerDegreesZ() const
	{
		return glm::degrees(_localRotationEuler.z);
	}

	glm::vec3 TransformComponent::GetScale() const
	{
		return _worldScale;
	}

	glm::vec2 TransformComponent::GetScaleXY() const
	{
		return { _worldScale.x, _worldScale.y };
	}

	glm::vec3 TransformComponent::GetLocalScale() const
	{
		return _localScale;
	}

	void TransformComponent::SetLocalPositionAsWorldPosition()
	{
		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return;

		const std::shared_ptr<Entity> parentEntity = entity->GetParent().lock();

		glm::vec3 parentWorldPosition = glm::vec3(0);

		if (parentEntity)
		{
			const std::shared_ptr<TransformComponent> parentTransform = parentEntity->GetTransform().lock();

			if (parentTransform)
			{
				parentWorldPosition = parentTransform->_worldPosition;
			}
		}

		_localPosition = _worldPosition - parentWorldPosition;

		ComposeLocalMatrix();
	}

	void TransformComponent::RecalculateLocalPosition()
	{
		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return;

		const std::shared_ptr<Entity> parentEntity = entity->GetParent().lock();

		glm::vec3 parentWorldPosition = glm::vec3(0);

		if (parentEntity)
		{
			const std::shared_ptr<TransformComponent> parentTransform = parentEntity->GetTransform().lock();

			if (parentTransform)
			{
				parentWorldPosition = parentTransform->_worldPosition;
			}
		}

		_localPosition = _worldPosition - parentWorldPosition;
	}

	void TransformComponent::RecalculateLocalRotation()
	{
		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return;

		const std::shared_ptr<Entity> parentEntity = entity->GetParent().lock();

		glm::quat parentWorldRotation = glm::quat();

		if (parentEntity)
		{
			const std::shared_ptr<TransformComponent> parentTransform = parentEntity->GetTransform().lock();

			if (parentTransform)
			{
				parentWorldRotation = parentTransform->_worldRotation;
			}
		}

		_localRotation = parentWorldRotation * _worldRotation;
		_localRotationEuler = glm::eulerAngles(_localRotation);
	}

	void TransformComponent::RecalculateChildrenHierarchyWorldMatrices() const
	{
		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return;

		entity->ForEachEntityInChildHierarchy(
			true,
			[this](const std::shared_ptr<Entity> &checkingEntity)
			{
				const std::shared_ptr<TransformComponent> childTransform = checkingEntity->GetTransform().lock();
				if (!childTransform) return;

				childTransform->RecalculateWorldMatrix();
			}
		);
	}

	void TransformComponent::ComposeLocalMatrix()
	{
		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return;

		constexpr glm::mat4 identityMatrix = glm::mat4(1.0f);

		const glm::mat4 translation = glm::translate(identityMatrix, _localPosition);

		const glm::quat normalizedRotation = glm::normalize(_localRotation);
		const glm::mat4 rotation = glm::toMat4(normalizedRotation);

		const glm::mat4 scaling = glm::scale(identityMatrix, _localScale);

		_localMatrix = translation * rotation * scaling;
	}

	void TransformComponent::RecalculateWorldMatrix()
	{
		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return;

		const std::shared_ptr<Entity> parentEntity = entity->GetParent().lock();

		glm::mat4 parentWorldMatrix = glm::mat4(1.0f);
		glm::vec3 parentWorldScale = glm::vec3(1.0f);

		if (parentEntity)
		{
			const std::shared_ptr<TransformComponent> parentTransform = parentEntity->GetTransform().lock();

			if (parentTransform)
			{
				parentWorldMatrix = parentTransform->_worldMatrix;
				parentWorldScale = parentTransform->_worldScale;
			}
		}

		_worldMatrix = parentWorldMatrix * _localMatrix;

		glm::vec3 skew;
		glm::vec4 perspective;
		glm::vec3 translation;
		glm::vec3 scale;
		glm::quat rotation;

		const bool success = glm::decompose(_worldMatrix, scale, rotation, translation, skew, perspective);

		if (success)
		{
			_worldPosition = translation;
			_worldRotation = rotation;

			_worldRotationEuler = glm::eulerAngles(_worldRotation);
		}

		_worldScale = parentWorldScale * _localScale;
	}
} // GEngineCore