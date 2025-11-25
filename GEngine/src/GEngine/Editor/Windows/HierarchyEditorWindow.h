//
// Created by guillem on 6/9/25.
//

#ifndef HIERARCHYEDITORWINDOW_H
#define HIERARCHYEDITORWINDOW_H
#include <vector>

#include "EditorWindow.h"

namespace GEngine
{
	class EditorModule;
	class EntitiesModule;
	class Entity;

	class HierarchyEditorWindow : public EditorWindow
	{
	public:
		explicit HierarchyEditorWindow(GEngineCoreModules* modules);

		void DrawWindowContent() override;

	private:
		void DrawRightClickContextMenu(
			EntitiesModule* entities,
			const std::shared_ptr<Entity>& entity
			);

		void DrawLeftClickContextMenu(
			EditorModule* editor,
			const std::shared_ptr<Entity>& entity
			);

	private:
		std::vector<std::pair<std::shared_ptr<Entity>, int>> _stack;
	};
}

#endif //HIERARCHYEDITORWINDOW_H
