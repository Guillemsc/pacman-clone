//
// Created by guillem on 7/1/25.
//

#include "IntPropertyDrawerEditor.h"

#include "imgui.h"

namespace GEngine
{
	void IntPropertyDrawerEditor::DrawSpecific(Property<int> *inspect)
	{
		int value = inspect->GetValue();
		if (ImGui::DragInt(inspect->GetName().c_str(), &value, 0.1f))
		{
			inspect->SetValue(value);
		}
	}
} // GEngine