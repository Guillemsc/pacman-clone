//
// Created by guillem on 6/9/25.
//

#include "InspectorEditorWindow.h"

#include "imgui.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Editor/Inspector/EntityInspectorEditor.h"
#include "GEngine/Editor/Inspector/ResourcesInspectorEditor.h"
#include "GEngine/Modules/EditorModule.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Resources/Resource.h"

namespace GEngine
{
	InspectorEditorWindow::InspectorEditorWindow(GEngineCoreModules* modules)
		: EditorWindow(modules, "Inspector")
	{
		RegisterInspectorEditor<EntityInspectorEditor, Entity>();
		RegisterInspectorEditor<ResourcesInspectorEditor, Resource>();
	}

	void InspectorEditorWindow::DrawWindowContent()
	{
		const std::shared_ptr<GEngineObject> selectedObject = _modules->editor->GetSelectedObject().lock();

		if (!selectedObject)
		{
			ImGui::Text("No selected object");
		}
		else
		{
			const std::shared_ptr<IGEngineObjectInspectorEditor> inspector = GetInspectorEditor(selectedObject->GetObjectType());

			if (!inspector)
			{
				ImGui::Text("Selected object cannot be inspected");
			}
			else
			{
				inspector->Draw(selectedObject);
			}
		}
	}

	std::shared_ptr<IGEngineObjectInspectorEditor> InspectorEditorWindow::GetInspectorEditor(const GEngineObjectType gEngineObjectType)
	{
		const std::size_t objectIndex = static_cast<std::size_t>(gEngineObjectType);

		if (_inspectorEditors.size() <= objectIndex)
		{
			return nullptr;
		}

		return _inspectorEditors[objectIndex];
	}
} // GEngineCore