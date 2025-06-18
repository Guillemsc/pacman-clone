//
// Created by guillem on 6/7/25.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include "Entities/Entity.h"

namespace GEngineCore
{
	class Component
	{
	friend class ComponentsModule;
	friend class Entity;

	public:
		explicit Component(const std::weak_ptr<Entity> &entity);
		virtual ~Component() = 0;

		std::weak_ptr<Entity> GetEntity() const;
		std::weak_ptr<GEngineCoreApplication> GetApp() const;

		bool IsEnanbled() const;
		void SetEnabled(bool enabled);

		virtual ComponentType GetType() = 0;
		virtual const char* GetTypeName() = 0;

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
