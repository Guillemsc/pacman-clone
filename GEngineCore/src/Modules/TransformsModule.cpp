//
// Created by guillem on 6/8/25.
//

#include "TransformsModule.h"

#include "EntitiesModule.h"
#include "Components/TransformComponent.h"

namespace GEngineCore
{
	void TransformsModule::RecalculateTransformLocalPosition(TransformComponent* transform)
	{
		const std::shared_ptr<Entity> entity = transform->GetEntity().lock();
		if (!entity) return;

		const std::shared_ptr<Entity> parentEntity = entity->GetParent().lock();

		Vector3 parentWorldPosition = Vector3Zero();

		if (parentEntity)
		{
			std::shared_ptr<TransformComponent> parentTransform = parentEntity->GetTransform().lock();

			if (parentTransform)
			{
				parentWorldPosition = parentTransform->_worldPosition;
			}
		}

		transform->_localPosition = transform->_worldPosition - parentWorldPosition;
	}

	void TransformsModule::RecalculateTransformLocalRotation(TransformComponent* transform)
	{
		const std::shared_ptr<Entity> entity = transform->GetEntity().lock();
		if (!entity) return;

		const std::shared_ptr<Entity> parentEntity = entity->GetParent().lock();

		Quaternion parentWorldRotation = QuaternionIdentity();

		if (parentEntity)
		{
			std::shared_ptr<TransformComponent> parentTransform = parentEntity->GetTransform().lock();

			if (parentTransform)
			{
				parentWorldRotation = parentTransform->_worldRotation;
			}
		}

		transform->_localRotation = QuaternionMultiply(QuaternionInvert(parentWorldRotation), transform->_worldRotation);
		transform->_localRotationEuler = QuaternionToEuler(transform->_localRotation);
	}

	void TransformsModule::RecalculateChildrenTransformsInHierarchyWorldMatrices(const TransformComponent* transform)
	{
		const std::shared_ptr<Entity> entity = transform->GetEntity().lock();
		if (!entity) return;

		entity->ForEachEntityInChildHierarchy(
			true,
			[this](const std::shared_ptr<Entity> &entity)
			{
				const std::shared_ptr<TransformComponent> childTransform = entity->GetTransform().lock();
				if (!childTransform) return;

				RebuildTransformWorldMatrix(childTransform.get());
			}
		);
	}

	void TransformsModule::ComposeTransformLocalMatrix(TransformComponent* transform)
	{
		const std::shared_ptr<Entity> entity = transform->GetEntity().lock();
		if (!entity) return;

		// Create transformation matrices
		const Matrix translation = MatrixTranslate(transform->_localPosition.x, transform->_localPosition.y, transform->_localPosition.z);
		const Matrix rotation = QuaternionToMatrix(QuaternionInvert(transform->_localRotation));
		const Matrix scaling = MatrixScale(transform->_localScale.x, transform->_localScale.y, transform->_localScale.z);

		// Combine: M = T * R * S
		transform->_localMatrix = MatrixMultiply(MatrixMultiply(scaling, rotation), translation);
	}

	void TransformsModule::RebuildTransformWorldMatrix(TransformComponent* transform)
	{
		const std::shared_ptr<Entity> entity = transform->GetEntity().lock();
		if (!entity) return;

		const std::shared_ptr<Entity> parentEntity = entity->GetParent().lock();

		Matrix parentWorldMatrix = MatrixIdentity();

		if (parentEntity)
		{
			std::shared_ptr<TransformComponent> parentTransform = parentEntity->GetTransform().lock();

			if (parentTransform)
			{
				parentWorldMatrix = parentTransform->_worldMatrix;
			}
		}

		transform->_worldMatrix = MatrixMultiply(transform->_localMatrix, parentWorldMatrix);

		MatrixDecompose(
			transform->_worldMatrix,
			&transform->_worldPosition,
			&transform->_worldRotation,
			&transform->_worldScale
			);

		transform->_worldRotation = QuaternionInvert(transform->_worldRotation);
		transform->_worldRotationEuler = QuaternionToEuler(transform->_worldRotation);
	}

	void TransformsModule::SetLocalPositionAsWorldPosition(TransformComponent* transform)
	{
		const std::shared_ptr<Entity> entity = transform->GetEntity().lock();
		if (!entity) return;

		const std::shared_ptr<Entity> parentEntity = entity->GetParent().lock();

		Vector3 parentWorldPosition = Vector3Zero();

		if (parentEntity)
		{
			std::shared_ptr<TransformComponent> parentTransform = parentEntity->GetTransform().lock();

			if (parentTransform)
			{
				parentWorldPosition = parentTransform->_worldPosition;
			}
		}

		transform->_localPosition = transform->_worldPosition - parentWorldPosition;

		ComposeTransformLocalMatrix(transform);
	}
}
