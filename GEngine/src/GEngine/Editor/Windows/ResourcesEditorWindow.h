//
// Created by guillem on 6/9/25.
//

#ifndef RESOURCESEDITORWINDOW_H
#define RESOURCESEDITORWINDOW_H

#include "EditorWindow.h"
#include "GEngine/Strings/StringBuilder.h"

namespace GEngine
{
	class Resource;
	class EditorModule;

	class ResourcesEditorWindow final : public EditorWindow
	{
	public:
		explicit ResourcesEditorWindow(GEngineCoreModules* modules);

		void DrawWindowContent() override;

	private:
		void DrawLeftClickContextMenu(
			EditorModule* editor,
			const std::shared_ptr<Resource> &resource
		);

	private:
		StringBuilder _stringBuilder;
	};
}

#endif //RESOURCESEDITORWINDOW_H
