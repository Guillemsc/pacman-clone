//
// Created by guillem on 6/9/25.
//

#ifndef RESOURCESEDITORWINDOW_H
#define RESOURCESEDITORWINDOW_H
#include "EditorWindow.h"

namespace GEngineCore
{
	class Resource;
	class EditorModule;

	class ResourcesEditorWindow : public EditorWindow
	{
	public:
		explicit ResourcesEditorWindow(const std::weak_ptr<GEngineCoreApplication> &app);

		void Draw() override;

	private:
		void DrawLeftClickContextMenu(
			const std::shared_ptr<EditorModule> &editor,
			const std::shared_ptr<Resource> &resource
		);
	};
}

#endif //RESOURCESEDITORWINDOW_H
