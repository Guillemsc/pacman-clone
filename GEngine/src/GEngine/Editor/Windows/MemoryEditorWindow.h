//
// Created by guillem on 12/14/25.
//

#ifndef MEMORYEDITORWINDOW_H
#define MEMORYEDITORWINDOW_H

#include "EditorWindow.h"

namespace GEngine
{
	class MemoryEditorWindow final : public EditorWindow
	{
	public:
		MemoryEditorWindow(GEngineCoreModules* modules);

		void DrawWindowContent() override;
	};
}

#endif //MEMORYEDITORWINDOW_H
