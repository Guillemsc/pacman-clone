//
// Created by guillem on 6/8/25.
//

#include "TickShapeRenderer2dComponentsSystem.h"

#include "Core/GEngineCoreApplication.h"

namespace GEngineCore
{
	TickShapeRenderer2dComponentsSystem::TickShapeRenderer2dComponentsSystem(const std::weak_ptr<GEngineCoreApplication> &app)
	{
		_app = app;
	}

	void TickShapeRenderer2dComponentsSystem::Tick()
	{
		// auto app = _app.lock();
		// if (!app) return;
		//
		// std::shared_ptr<ComponentsModule> components = app->Components().lock();
		// if (!components) return;
		//
		// std::shared_ptr<RenderingModule> rendering = app->Rendering().lock();
		// if (!rendering) return;
		//
		// std::weak_ptr<ComponentArray<ShapeRenderer2dComponent>> componentsArrayPtr = components->GetComponentArray<ShapeRenderer2dComponent>();
		//
		// std::shared_ptr<ComponentArray<ShapeRenderer2dComponent>> componentsArray = componentsArrayPtr.lock();
		// if (!componentsArray) return;
		//
		// const std::vector<std::shared_ptr<ShapeRenderer2dComponent>>& componentsList = componentsArray->GetComponents();
		//
		// int count = 2;
		// for (auto it = componentsList.begin(); it != componentsList.end(); ++it)
		// {
		// 	const Entity entity = (*it)->GetEntity();
		// 	std::weak_ptr<TransformComponent> transformPtr = components->GetComponent<TransformComponent>(entity);
		//
		// 	if (transformPtr.expired()) continue;
		//
		// 	rendering->Renderer2D().lock()->Add(0, [count]()
		// 	{
		// 		DrawText("Hello, raylib!", 190 * count, 200, 20, LIGHTGRAY);
		// 	});
		//
		// 	++count;
		// }
	}
} // GEngineCore