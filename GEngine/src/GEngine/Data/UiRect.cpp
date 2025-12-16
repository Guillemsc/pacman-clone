//
// Created by guillem on 7/8/25.
//

#define GLM_ENABLE_EXPERIMENTAL

#include "UiRect.h"

#include <cmath>

#include "GEngine/Extensions/Vec2Extensions.h"
#include "GEngine/Extensions/Vec4Extensions.h"
#include "GEngine/Logging/GEngineLog.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/quaternion.hpp"

namespace GEngine
{
	UiRect UiRect::Transform(const UiRect &parent, const UiRect &child)
	{
		const glm::mat4 childMatrix = child.BuildMatrix();
		const glm::mat4 parentMatrix = parent.BuildMatrix();

		glm::mat4 worldMatrix = parentMatrix * childMatrix;

		glm::vec3 skew;
		glm::vec4 perspective;
		glm::vec3 translation;
		glm::vec3 scale;
		glm::quat rotation;

		glm::decompose(worldMatrix, scale, rotation, translation, skew, perspective);

		glm::vec3 eulerRotation = glm::eulerAngles(rotation);

		UiRect global;
		global.position = { translation.x, translation.y };
		global.rotation = eulerRotation.z;
		global.scale = { scale.x, scale.y };

		global.size = global.scale * child.size;
		global.pivot = { 0.5f, 0.5f };

		return global;
	}

	glm::mat4 UiRect::BuildMatrix() const
	{
		const glm::vec2 pivotOffset = GetPivotOffset();;
		const glm::vec3 matrixPivotOffset = glm::vec3(pivotOffset.x, pivotOffset.y, 0);
		const glm::vec3 matrixPosition = { position.x - pivotOffset.x, position.y - pivotOffset.y, 0 };
		const glm::quat matrixRotationQuaternion = glm::angleAxis(rotation, glm::vec3(0, 0, 1));
		const glm::quat normalizedRotation = glm::normalize(matrixRotationQuaternion);
		const glm::vec3 matrixScale = { scale.x, scale.y, 1 };

		constexpr glm::mat4 identityMatrix = glm::mat4(1.0f);

		const glm::mat4 translationMat = glm::translate(identityMatrix, matrixPosition);
		const glm::mat4 rotationMat = glm::toMat4(normalizedRotation);
		const glm::mat4 scaleMat = glm::scale(identityMatrix, matrixScale);
		const glm::mat4 pivotToOriginMat = glm::translate(identityMatrix, -matrixPivotOffset);
		const glm::mat4 pivotBackMat = glm::translate(identityMatrix, matrixPivotOffset);

		return translationMat * pivotBackMat * rotationMat * scaleMat * pivotToOriginMat;
	}

	glm::vec2 UiRect::GetPositionWithAppliedPivot() const
	{
		const glm::vec2 offset = GetPivotOffset();
		return position + offset;
	}

	glm::vec2 UiRect::GetPivotOffset(const glm::vec2 &pivot) const
	{
		return (pivot - glm::vec2(0.5f)) * size;
	}

	glm::vec2 UiRect::GetPivotOffset() const
	{
		return GetPivotOffset(pivot);
	}

	glm::vec2 UiRect::GetPivotPosition(const glm::vec2& pivot) const
	{
		glm::vec2 pivotOffset = GetPivotOffset(pivot);
		pivotOffset = MathExtensions::RotatePointAroundOrigin(pivotOffset, rotation);
		return position + pivotOffset;
	}

	glm::vec2 UiRect::GetPivotPosition() const
	{
		return GetPivotPosition(pivot);
	}

	CornersRect UiRect::GetCorners() const
	{
		CornersRect corners;

		const glm::vec2 pivotOffset = GetPivotOffset();
		const glm::vec2 halfSize = size * 0.5f;

		corners.bottomLeft = glm::vec2(-halfSize.x, -halfSize.y) + pivotOffset;
		corners.topLeft = glm::vec2(-halfSize.x, halfSize.y) + pivotOffset;
		corners.topRight = glm::vec2(halfSize.x, halfSize.y) + pivotOffset;
		corners.bottomRight = glm::vec2(halfSize.x, -halfSize.y) + pivotOffset;

		corners.bottomLeft = position + MathExtensions::RotatePointAroundPivot(corners.bottomLeft, pivotOffset, rotation);
		corners.topLeft = position + MathExtensions::RotatePointAroundPivot(corners.topLeft, pivotOffset, rotation);
		corners.topRight = position + MathExtensions::RotatePointAroundPivot(corners.topRight, pivotOffset, rotation);
		corners.bottomRight = position + MathExtensions::RotatePointAroundPivot(corners.bottomRight, pivotOffset, rotation);

		return corners;
	}

	glm::vec2 UiRect::InversePoint(const glm::vec2 &point) const
	{
		const glm::mat4 matrix = BuildMatrix();
		const glm::mat4 inverseMatrix = glm::inverse(matrix);
		const glm::vec4 local = inverseMatrix * glm::vec4(point, 0.0f, 1.0f);
		return { local.x, local.y };
	}

	bool UiRect::ContainsPoint(const glm::vec2 &point) const
	{
		const glm::vec2 local = InversePoint(point);

		// We need to account for the positional offset of the rect bounds
		const glm::vec2 finalSize = Vec2Extensions::SafeDivide(size, scale);
		const float x = -pivot.x * finalSize.x;
		const float y = -pivot.y * finalSize.y;
		const float w = x + finalSize.x;
		const float h = y + finalSize.y;

		return local.x >= x && local.x <= w &&
			   local.y >= y && local.y <= h;
	}
} // GEngine