//
// Created by guillem on 6/7/25.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include "GEngine/Entities/Entity.h"
#include "GEngine/SerializedProperties/PropertiesContainer.h"

namespace GEngine
{
	class Component : public GEngineObject
	{
	friend class ComponentsModule;
	friend class Entity;

	public:
		explicit Component(const std::weak_ptr<Entity> &entity);

		std::weak_ptr<Entity> GetEntity() const;
		std::weak_ptr<GEngineCoreApplication> GetApp() const;

		bool IsEnanbled() const;
		void SetEnabled(bool enabled);

		virtual constexpr const char* GetTypeName() = 0;

	protected:
		virtual void OnAwake() {}
		virtual void OnEnable() {}
		virtual void OnTick() {};
		virtual void OnDisable() {}
		virtual void OnDestroy() {}

	private:
		void RefreshEnabledState();

	private:
		std::weak_ptr<Entity> _entity;

		bool _isEnabledSelf = false;
		bool _isEnabledInHierarchy = false;
	};
}

#endif //COMPONENT_H
