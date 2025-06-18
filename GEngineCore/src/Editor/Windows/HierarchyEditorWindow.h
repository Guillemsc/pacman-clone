//
// Created by guillem on 6/9/25.
//

#ifndef HIERARCHYEDITORWINDOW_H
#define HIERARCHYEDITORWINDOW_H
#include <vector>

#include "EditorWindow.h"

namespace GEngineCore
{
	class EditorModule;
	class EntitiesModule;
	class Entity;

	class HierarchyEditorWindow : public EditorWindow
	{
	public:
		explicit HierarchyEditorWindow(const std::weak_ptr<GEngineCoreApplication> &app);

		void Draw() override;

	private:
		void DrawRightClickContextMenu(
			const std::shared_ptr<EntitiesModule>& entities,
			const std::shared_ptr<Entity>& entity
			);

		void DrawLeftClickContextMenu(
			const std::shared_ptr<EditorModule>& editor,
			const std::shared_ptr<Entity>& entity
			);

	private:
		std::vector<std::pair<std::shared_ptr<Entity>, int>> _stack;
	};
}

#endif //HIERARCHYEDITORWINDOW_H
