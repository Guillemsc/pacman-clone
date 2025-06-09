//
// Created by guillem on 6/9/25.
//

#ifndef RESOURCESEDITORWINDOW_H
#define RESOURCESEDITORWINDOW_H
#include "EditorWindow.h"

namespace GEngineCore
{
	class ResourcesEditorWindow : public EditorWindow
	{
	public:
		explicit ResourcesEditorWindow(const std::weak_ptr<GEngineCoreApplication> &app);

		void Draw() override;
	};
}

#endif //RESOURCESEDITORWINDOW_H
