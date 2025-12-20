//
// Created by guillem on 12/19/25.
//

#ifndef VIEW_H
#define VIEW_H

#include <memory>

#include "GEngine/Entities/Entity.h"
#include "GEngine/Scenes/Scene.h"
#include "GEngine/Components/UiTransformComponent.h"

namespace GEngine
{
	class GEngineCoreModules;
}

namespace PacMan
{
	class UiView
	{
	public:
		explicit UiView(
			GEngine::GEngineCoreModules* modules,
			GEngine::Scene* scene,
			const std::string& name
			);

		template <typename T>
		static std::shared_ptr<T> Create(
			GEngine::GEngineCoreModules* modules,
			GEngine::Scene* scene
			);

		void Dispose() const;

		virtual void BuildTree(const std::shared_ptr<GEngine::Entity>& root) = 0;

	protected:
		GEngine::GEngineCoreModules* const _modules;
		GEngine::Scene* const _scene;
		const std::string _name;

		std::weak_ptr<GEngine::Entity> _rootEntity;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<typename T>
	std::shared_ptr<T> UiView::Create(GEngine::GEngineCoreModules *modules, GEngine::Scene *scene)
	{
		std::shared_ptr<T> view = std::make_shared<T>(modules, scene);

		const std::shared_ptr<GEngine::Entity> root = scene->AddUiEntity().lock();
		root->SetName(view->_name);
		root->GetUiTransform().lock()->ExpandOnParent();

		view->_rootEntity = root;

		view->BuildTree(root);

		return view;
	}
}

#endif //VIEW_H
