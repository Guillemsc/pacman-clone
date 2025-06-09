//
// Created by guillem on 6/7/25.
//

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "Component.h"
#include "ComponentType.h"
#include "raylib.h"
#include "raymath.h"

namespace GEngineCore
{
	class TransformComponent : public Component, public std::enable_shared_from_this<TransformComponent>
	{
		friend class TransformsModule;

	public:
		explicit TransformComponent(const std::weak_ptr<Entity> &entity);
		~TransformComponent() override;

		static ComponentType GetTypeStatic() { return ComponentType::TRANSFORM; }
		ComponentType GetType() override { return GetTypeStatic(); }
		const char* GetTypeName() override { return "Transform"; }

		void SetPosition(const Vector3 &position);
		void SetLocalPosition(const Vector3 &position);
		void SetRotation(const Quaternion &rotation);

		void SetLocalRotation(const Quaternion &rotation);
		void SetLocalRotationEuler(const Vector3 &rotation);
		void SetLocalRotationEulerDegrees(const Vector3 &rotation);
		void SetLocalRotationEulerDegreesZ(float rotationZ);

		void SetLocalScale(const Vector3 &scale);

		Vector3 GetPosition() const;
		Vector3 GetLocalPosition() const;

		Quaternion GetLocalRotation() const;
		Vector3 GetLocalRotationEuler() const;
		Vector3 GetLocalRotationEulerDegrees() const;
		float GetRotationEulerZ() const;
		float GetRotationEulerDegreesZ() const;
		float GetLocalRotationEulerZ() const;
		float GetLocalRotationEulerDegreesZ() const;

	private:
		Vector3 _worldPosition = Vector3Zero();
		Quaternion _worldRotation = QuaternionIdentity();
		Vector3 _worldRotationEuler = Vector3Zero();
		Vector3 _worldScale = Vector3One();
		Matrix _worldMatrix = MatrixIdentity();

		Vector3 _localPosition = Vector3Zero();
		Quaternion _localRotation = QuaternionIdentity();
		Vector3 _localRotationEuler = Vector3Zero();
		Vector3 _localScale = Vector3One();
		Matrix _localMatrix = MatrixIdentity();
	};
}

#endif //TRANSFORMCOMPONENT_H
