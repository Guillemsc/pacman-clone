//
// Created by guillem on 6/7/25.
//

#include "TransformComponent.h"

#include "Modules/TransformsModule.h"

namespace GEngineCore
{
	TransformComponent::TransformComponent(const std::weak_ptr<Entity> &entity) : Component(entity)
	{

	}

	TransformComponent::~TransformComponent()
	{
	}

	void TransformComponent::SetPosition(const Vector3 &position)
	{
		const std::shared_ptr<GEngineCoreApplication> app = GetApp().lock();
		if (app == nullptr) return;

		const std::shared_ptr<TransformsModule> transforms = app->Transforms().lock();
		if (transforms == nullptr) return;

		if (Vector3Equals(_worldPosition, position))
		{
			return;
		}

		_worldPosition = position;

		transforms->RecalculateTransformLocalPosition(this);
		transforms->ComposeTransformLocalMatrix(this);
		transforms->RecalculateChildrenTransformsInHierarchyWorldMatrices(this);
	}

	void TransformComponent::SetLocalPosition(const Vector3 &position)
	{
		const std::shared_ptr<GEngineCoreApplication> app = GetApp().lock();
		if (app == nullptr) return;

		const std::shared_ptr<TransformsModule> transforms = app->Transforms().lock();
		if (transforms == nullptr) return;

		if (Vector3Equals(_localPosition, position))
		{
			return;
		}

		_localPosition = position;

		const std::shared_ptr<TransformComponent> thisShared = shared_from_this();

		transforms->ComposeTransformLocalMatrix(this);
		transforms->RecalculateChildrenTransformsInHierarchyWorldMatrices(this);
	}

	void TransformComponent::SetRotation(const Quaternion &rotation)
	{
		const std::shared_ptr<GEngineCoreApplication> app = GetApp().lock();
		if (app == nullptr) return;

		const std::shared_ptr<TransformsModule> transforms = app->Transforms().lock();
		if (transforms == nullptr) return;

		if (QuaternionEquals(_worldRotation, rotation))
		{
			return;
		}

		_worldRotation = rotation;

		transforms->RecalculateTransformLocalRotation(this);
		transforms->ComposeTransformLocalMatrix(this);
		transforms->RecalculateChildrenTransformsInHierarchyWorldMatrices(this);
	}

	void TransformComponent::SetLocalRotation(const Quaternion &rotation)
	{
		const std::shared_ptr<GEngineCoreApplication> app = GetApp().lock();
		if (app == nullptr) return;

		const std::shared_ptr<TransformsModule> transforms = app->Transforms().lock();
		if (transforms == nullptr) return;

		if (QuaternionEquals(_localRotation, rotation))
		{
			return;
		}

		_localRotation = rotation;

		transforms->ComposeTransformLocalMatrix(this);
		transforms->RecalculateChildrenTransformsInHierarchyWorldMatrices(this);
	}

	void TransformComponent::SetLocalRotationEuler(const Vector3 &rotation)
	{
		const std::shared_ptr<GEngineCoreApplication> app = GetApp().lock();
		if (app == nullptr) return;

		const std::shared_ptr<TransformsModule> transforms = app->Transforms().lock();
		if (transforms == nullptr) return;

		if (Vector3Equals(_localRotationEuler, rotation))
		{
			return;
		}

		_localRotationEuler = rotation;

		const Quaternion quaternion = QuaternionFromEuler(_localRotationEuler.x, _localRotationEuler.y, _localRotationEuler.z);
		SetLocalRotation(quaternion);
	}

	void TransformComponent::SetLocalRotationEulerDegrees(const Vector3 &rotation)
	{
		const Vector3 rotationRadians = {rotation.x * DEG2RAD, rotation.y * DEG2RAD, rotation.z * DEG2RAD};
		SetLocalRotationEuler(rotationRadians);
	}

	void TransformComponent::SetLocalRotationEulerDegreesZ(float rotationZ)
	{
		float rotationRadiansZ = rotationZ * DEG2RAD;
		Vector3 rotationRadians = Vector3(_localRotationEuler.x, _localRotationEuler.y, rotationRadiansZ);
		SetLocalRotationEuler(rotationRadians);
	}

	void TransformComponent::SetLocalScale(const Vector3 &scale)
	{
		const std::shared_ptr<GEngineCoreApplication> app = GetApp().lock();
		if (app == nullptr) return;

		const std::shared_ptr<TransformsModule> transforms = app->Transforms().lock();
		if (transforms == nullptr) return;

		if (Vector3Equals(_localScale, scale))
		{
			return;
		}

		_localScale = scale;

		transforms->ComposeTransformLocalMatrix(this);
		transforms->RecalculateChildrenTransformsInHierarchyWorldMatrices(this);
	}

	Vector3 TransformComponent::GetPosition() const
	{
		return _worldPosition;
	}

	Vector3 TransformComponent::GetLocalPosition() const
	{
		return _localPosition;
	}

	Quaternion TransformComponent::GetLocalRotation() const
	{
		return _localRotation;
	}

	Vector3 TransformComponent::GetLocalRotationEuler() const
	{
		return _localRotationEuler;
	}

	Vector3 TransformComponent::GetLocalRotationEulerDegrees() const
	{
		return {_localRotationEuler.x * RAD2DEG, _localRotationEuler.y * RAD2DEG, _localRotationEuler.z * RAD2DEG};
	}

	float TransformComponent::GetRotationEulerZ() const
	{
		return _worldRotationEuler.z;
	}

	float TransformComponent::GetRotationEulerDegreesZ() const
	{
		return _worldRotationEuler.z * RAD2DEG;
	}

	float TransformComponent::GetLocalRotationEulerZ() const
	{
		return _localRotationEuler.z;
	}

	float TransformComponent::GetLocalRotationEulerDegreesZ() const
	{
		return _localRotationEuler.z * RAD2DEG;
	}
} // GEngineCore