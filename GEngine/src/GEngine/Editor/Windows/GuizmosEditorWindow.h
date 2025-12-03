//
// Created by guillem on 12/2/25.
//

#ifndef GUIZMOSEDITORWINDOW_H
#define GUIZMOSEDITORWINDOW_H

#include "EditorWindow.h"

namespace GEngine
{
	class GEngineCoreModules;

	class GuizmosEditorWindow final : public EditorWindow
	{
	public:
		explicit GuizmosEditorWindow(GEngineCoreModules* modules);

		void DrawWindowContent() override;
	};

} // GEmgome

#endif //GUIZMOSEDITORWINDOW_H
