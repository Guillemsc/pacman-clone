//
// Created by guillem on 6/9/25.
//

#ifndef RESOURCESEDITORWINDOW_H
#define RESOURCESEDITORWINDOW_H
#include "EditorWindow.h"

namespace GEngine
{
	class Resource;
	class EditorModule;

	class ResourcesEditorWindow : public EditorWindow
	{
	public:
		explicit ResourcesEditorWindow(GEngineCoreModules* modules);

		void DrawWindowContent() override;

	private:
		void DrawLeftClickContextMenu(
			EditorModule* editor,
			const std::shared_ptr<Resource> &resource
		);
	};
}

#endif //RESOURCESEDITORWINDOW_H
