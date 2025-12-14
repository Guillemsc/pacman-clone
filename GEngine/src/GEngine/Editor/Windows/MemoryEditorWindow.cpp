//
// Created by guillem on 12/14/25.
//

#include "MemoryEditorWindow.h"

#include "imgui.h"
#include "GEngine/Memory/MemoryTracker.h"

namespace GEngine
{
	MemoryEditorWindow::MemoryEditorWindow(GEngineCoreModules* modules)
		: EditorWindow(modules, "Memory")
	{
	}

	void MemoryEditorWindow::DrawWindowContent()
	{
		ImGui::Text("Allocated: %ld", MemoryTracker::totalAllocated.load());
		ImGui::Text("Freed: %ld", MemoryTracker::totalFreed.load());
		ImGui::Text("Used: %ld", MemoryTracker::CurrentlyUsed());
	}
}
