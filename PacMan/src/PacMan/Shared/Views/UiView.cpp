//
// Created by guillem on 12/19/25.
//

#include "UiView.h"

namespace PacMan
{
	UiView::UiView(GEngine::GEngineCoreModules *modules, GEngine::Scene *scene, const std::string &name)
		: _modules(modules), _scene(scene), _name(name)
	{
	}

	void UiView::Dispose() const
	{
		_scene->RemoveEntity(_rootEntity);
	}
}
