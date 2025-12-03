//
// Created by guillem on 12/3/25.
//

#ifndef COLLISIONS2DEDITORWINDOW_H
#define COLLISIONS2DEDITORWINDOW_H
#include "EditorWindow.h"

namespace GEngine
{
	class GEngineCoreModules;

	class Collisions2dEditorWindow final : public EditorWindow
	{
	public:
		explicit Collisions2dEditorWindow(GEngineCoreModules* modules);

		void DrawWindowContent() override;
	};
}

#endif //COLLISIONS2DEDITORWINDOW_H
