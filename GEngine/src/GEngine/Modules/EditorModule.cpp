//
// Created by guillem on 6/9/25.
//

#include "EditorModule.h"

#include "imgui.h"
#include "RenderingModule.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Editor/MenuBar/MenuBarEditor.h"
#include "GEngine/Editor/PropertyDrawers/Vec3PropertyDrawerEditor.h"
#include "GEngine/Editor/Windows/EditorWindow.h"
#include "GEngine/Editor/Windows/HierarchyEditorWindow.h"
#include "GEngine/Editor/Windows/InspectorEditorWindow.h"
#include "GEngine/Editor/Windows/ResourcesEditorWindow.h"
#include "GEngine/Extensions/UnorderedMapExtensions.h"
#include "GEngine/Rendering/ImGuiRenderer.h"

namespace GEngine
{
	void EditorModule::Init(const std::weak_ptr<GEngineCoreApplication> &app)
	{
		_app = app;

		_menuBar = std::make_shared<MenuBarEditor>(app);

		RegisterPropertyDrawer<Vec3PropertyDrawerEditor, SerializedProperty<glm::vec3>>();

		RegisterWindow<HierarchyEditorWindow>();
		RegisterWindow<InspectorEditorWindow>();
		RegisterWindow<ResourcesEditorWindow>();
	}

	void EditorModule::Tick()
	{
		RenderEditor();
	}

	void EditorModule::Dispose()
	{
	}

	void EditorModule::DrawProperty(ISerializedProperty *property) const
	{
		const std::type_index typeIndex = typeid(*property);

		const std::optional<std::shared_ptr<IPropertyDrawerEditor>> optional = UnorderedMapExtensions::GetValue(_propertyDrawers, typeIndex);

		if (!optional.has_value())
		{
			return;
		}

		optional.value()->Draw(property);
	}

	void EditorModule::SetSelectedObject(const std::weak_ptr<GEngineObject> &object)
	{
		_selectedObject = object;
	}

	std::weak_ptr<GEngineObject> EditorModule::GetSelectedObject() const
	{
		return _selectedObject;
	}

	void EditorModule::RenderEditor()
	{
		const std::shared_ptr<GEngineCoreApplication> app = _app.lock();
		if (app == nullptr) return;

		const std::shared_ptr<RenderingModule> rendering = app->Rendering().lock();
		if (rendering == nullptr) return;

		const std::shared_ptr<ImGuiRenderer> imGuiRenderer = rendering->ImGuiRender().lock();
		if (imGuiRenderer == nullptr) return;

		imGuiRenderer->Add([this]()
		{
			bool open = true;
			ImGui::ShowDemoWindow(&open);

			_menuBar->Draw();

			DrawWindows();
		});
	}

	void EditorModule::DrawWindows()
	{
		for (auto it = _windows.begin(); it != _windows.end(); ++it)
		{
			if (!(*it)->visible)
			{
				continue;
			}

			(*it)->Draw();
		}
	}
} // GEngineCore