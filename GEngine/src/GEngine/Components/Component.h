//
// Created by guillem on 6/7/25.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include "GEngine/Entities/Entity.h"
#include "GEngine/SerializedProperties/PropertiesContainer.h"

namespace GEngine
{
	class GuizmoUiRenderer;

	class Component : public GEngineObject
	{
		friend class ComponentsModule;
		friend class Entity;
		friend class EntityInspectorEditor;

	public:
		explicit Component(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity);

		std::weak_ptr<Entity> GetEntity() const;

		bool IsEnanbled() const;
		void SetEnabled(bool enabled);

		virtual constexpr const char* GetTypeName() = 0;

	protected:
		virtual void OnAwake() {}
		virtual void OnEnable() {}
		virtual void OnTick() {};
		virtual void OnDisable() {}
		virtual void OnDestroy() {}
		virtual void OnDrawSelectedGuizmo(GuizmoUiRenderer* guizmoUiRenderer) {}

	private:
		void RefreshEnabledState();

	public:
		GEngineCoreModules* const modules = nullptr;

	protected:
		const std::weak_ptr<Entity> _entity;

	private:
		bool _isEnabledSelf = false;
		bool _isEnabledInHierarchy = false;
	};
}

#endif //COMPONENT_H
