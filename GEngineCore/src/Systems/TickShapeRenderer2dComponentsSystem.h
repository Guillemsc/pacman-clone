//
// Created by guillem on 6/8/25.
//

#ifndef TICKSHAPERENDERER2DCOMPONENTSSYSTEM_H
#define TICKSHAPERENDERER2DCOMPONENTSSYSTEM_H
#include <memory>

#include "System.h"

namespace GEngineCore
{
	class GEngineCoreApplication;

	class TickShapeRenderer2dComponentsSystem : public System
	{
	public:
		explicit TickShapeRenderer2dComponentsSystem(const std::weak_ptr<GEngineCoreApplication>& app);

		void Tick() override;

	private:
		std::weak_ptr<GEngineCoreApplication> _app;
	};
}

#endif //TICKSHAPERENDERER2DCOMPONENTSSYSTEM_H
