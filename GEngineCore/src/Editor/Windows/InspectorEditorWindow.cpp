//
// Created by guillem on 6/9/25.
//

#include "InspectorEditorWindow.h"

#include "imgui.h"
#include "Core/GEngineCoreApplication.h"
#include "Editor/Inspector/EntityInspectorEditor.h"
#include "Modules/EditorModule.h"
#include "Entities/Entity.h"

namespace GEngineCore
{
	InspectorEditorWindow::InspectorEditorWindow(const std::weak_ptr<GEngineCoreApplication> &app): EditorWindow(app)
	{
		RegisterInspectorEditor<EntityInspectorEditor, Entity>();
	}

	void InspectorEditorWindow::Draw()
	{
		const std::shared_ptr<GEngineCoreApplication> app = _app.lock();
		if (!app) return;

		const std::shared_ptr<EditorModule> editor = app->Editor().lock();
		if (!editor) return;

		ImGui::Begin("Inspector");

		const std::shared_ptr<GEngineObject> selectedObject = editor->GetSelectedObject().lock();

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

		ImGui::End();
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