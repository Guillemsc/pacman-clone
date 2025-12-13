//
// Created by guillem on 6/7/25.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include "GEngine/Entities/Entity.h"
#include "GEngine/SerializedProperties/PropertiesContainer.h"
#include "GEngine/ComponentsRegister/ComponentsRegister.h"

namespace GEngine
{
	class GuizmoUiRenderer;

	class Component : public GEngineObject
	{
		friend class ComponentsModule;
		friend class GuizmosModule;
		friend class Entity;
		friend class EntityInspectorEditor;

	public:
		explicit Component(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity);

		[[nodiscard]] std::weak_ptr<Entity> GetEntity() const;

		void SetEnabled(bool enabled);
		[[nodiscard]] bool IsEnabled() const;

		[[nodiscard]] virtual constexpr const char* GetTypeName() const = 0;

	protected:
		virtual void OnAwake() {}
		virtual void OnEnable() {}
		virtual void OnTick() {};
		virtual void OnDisable() {}
		virtual void OnDestroy() {}
		virtual void OnDrawSelectedGuizmo() {}
		virtual void OnDrawGuizmo() {}

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

#define REGISTER_COMPONENT(TYPE)                                 \
public:                                                         \
	static constexpr const char* StaticTypeName() { return #TYPE; } \
	constexpr const char* GetTypeName() const override { return TYPE::StaticTypeName(); } \
private:                                                        \
	inline static const GEngine::ComponentsRegister _reg_##TYPE{ TYPE::StaticTypeName() };

#endif //COMPONENT_H
