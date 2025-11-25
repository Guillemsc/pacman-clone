//
// Created by guillem on 6/8/25.
//

#ifndef TICKSHAPERENDERER2DCOMPONENTSSYSTEM_H
#define TICKSHAPERENDERER2DCOMPONENTSSYSTEM_H
#include <memory>

#include "System.h"
#include "GEngine/Core/GEngineCoreModules.h"

namespace GEngine
{
	class GEngineCoreApplication;

	class TickShapeRenderer2dComponentsSystem : public System
	{
	public:
		explicit TickShapeRenderer2dComponentsSystem(GEngineCoreModules* modules);

		void Tick() override;

	private:
		GEngineCoreModules* const _modules;
	};
}

#endif //TICKSHAPERENDERER2DCOMPONENTSSYSTEM_H
