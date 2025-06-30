//
// Created by guillem on 6/7/25.
//

#include "ComponentsModule.h"

#include "GEngine/Components/CameraComponent.h"
#include "GEngine/Components/Shape2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Components/Texture2dRendererComponent.h"
#include "GEngine/Components/TiledMap2dRendererComponent.h"

namespace GEngine
{
	ComponentsModule::ComponentsModule()
	{

	}

	void ComponentsModule::Dispose()
	{
		_componentFactories.clear();
	}

	void ComponentsModule::TickEntityComponents(Entity* entityPtr)
	{
		for (auto it = entityPtr->_components.begin(); it != entityPtr->_components.end(); ++it)
		{
			if (!(*it)->_isEnabledInHierarchy)
			{
				continue;
			}

			(*it)->OnTick();
		}
	}
} // GEngineCore