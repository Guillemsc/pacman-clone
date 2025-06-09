//
// Created by guillem on 6/8/25.
//

#ifndef TRANSFORMSMODULE_H
#define TRANSFORMSMODULE_H

#include <memory>

namespace GEngineCore
{
	class TransformComponent;

	class TransformsModule
	{
		friend class Entity;

	public:
		void RecalculateTransformLocalPosition(TransformComponent* transform);
		void RecalculateTransformLocalRotation(TransformComponent* transform);
		void RecalculateChildrenTransformsInHierarchyWorldMatrices(const TransformComponent* transform);
		void ComposeTransformLocalMatrix(TransformComponent* transform);
		void RebuildTransformWorldMatrix(TransformComponent* transform);
		void SetLocalPositionAsWorldPosition(TransformComponent* transform);
	};
}

#endif //TRANSFORMSMODULE_H
