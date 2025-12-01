//
// Created by guillem on 6/9/25.
//

#include "EditorModule.h"

#include "imgui.h"
#include "GEngine/Raylib/RaylibWrapper.h"
#include "RenderingModule.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Editor/MenuBar/MenuBarEditor.h"
#include "GEngine/Editor/PropertyDrawers/Color01PropertyDrawerEditor.h"
#include "GEngine/Editor/PropertyDrawers/FloatPropertyDrawerEditor.h"
#include "GEngine/Editor/PropertyDrawers/IntPropertyDrawerEditor.h"
#include "GEngine/Editor/PropertyDrawers/Vec2PropertyDrawerEditor.h"
#include "GEngine/Editor/PropertyDrawers/Vec3PropertyDrawerEditor.h"
#include "GEngine/Editor/PropertyDrawers/Vec4PropertyDrawerEditor.h"
#include "GEngine/Editor/Windows/DemoEditorWindow.h"
#include "GEngine/Editor/Windows/EditorWindow.h"
#include "GEngine/Editor/Windows/ExamplesEditorWindow.h"
#include "GEngine/Editor/Windows/HierarchyEditorWindow.h"
#include "GEngine/Editor/Windows/InspectorEditorWindow.h"
#include "GEngine/Editor/Windows/ResourcesEditorWindow.h"
#include "GEngine/Editor/Windows/UiEditorWindow.h"
#include "GEngine/Extensions/UnorderedMapExtensions.h"
#include "GEngine/Objects/GEngineObject.h"
#include "GEngine/Rendering/ImGuiRenderer.h"
#include "glm/vec4.hpp"

namespace GEngine
{
	void EditorModule::Init(GEngineCoreModules* modules)
	{
		_modules = modules;

		_menuBar = std::make_shared<MenuBarEditor>(_modules);

		RegisterPropertyDrawer<IntPropertyDrawerEditor, Property<int>>();
		RegisterPropertyDrawer<FloatPropertyDrawerEditor, Property<float>>();
		RegisterPropertyDrawer<Vec2PropertyDrawerEditor, Property<glm::vec2>>();
		RegisterPropertyDrawer<Vec3PropertyDrawerEditor, Property<glm::vec3>>();
		RegisterPropertyDrawer<Vec4PropertyDrawerEditor, Property<glm::vec4>>();
		RegisterPropertyDrawer<Color01PropertyDrawerEditor, Property<Color01>>();

		RegisterWindow<HierarchyEditorWindow>();
		RegisterWindow<InspectorEditorWindow>();
		RegisterWindow<ResourcesEditorWindow>();
		RegisterWindow<UiEditorWindow>();
		RegisterWindow<ExamplesEditorWindow>();
		RegisterWindow<DemoEditorWindow>();
	}

	void EditorModule::Tick()
	{
		RenderEditor();

		if (IsKeyPressed(KeyboardKey::KEY_F1))
		{
			_editorRenderingEnabled = !_editorRenderingEnabled;
		}
	}

	void EditorModule::Dispose()
	{
	}

	void EditorModule::DrawProperty(IProperty *property) const
	{
		const std::shared_ptr<GEngineObject> object = property->GetObjectValue().lock();

		if (object)
		{
			DrawObject(object.get());
			return;
		}

		const std::type_index typeIndex = typeid(*property);

		const std::optional<std::shared_ptr<IPropertyDrawerEditor>> optional = UnorderedMapExtensions::GetValue(_propertyDrawers, typeIndex);

		if (!optional.has_value())
		{
			return;
		}

		optional.value()->Draw(property);
	}

	void EditorModule::DrawObject(const GEngineObject *gEngineObject) const
	{
		const PropertiesContainer& constainer = gEngineObject->GetProperties();
		const std::vector<std::shared_ptr<IProperty>>& properties = constainer.GetProperties();

		ImGui::Text(gEngineObject->GetObjectTypeName());

		for (auto it = properties.begin(); it != properties.end(); ++it)
		{
			DrawProperty(it->get());
		}
	}

	void EditorModule::SetSelectedObject(const std::weak_ptr<GEngineObject> &object)
	{
		_selectedObject = object;
	}

	std::weak_ptr<GEngineObject> EditorModule::GetSelectedObject() const
	{
		return _selectedObject;
	}

	const std::vector<std::shared_ptr<EditorWindow>> & EditorModule::GetEditorWindows() const
	{
		return _windows;
	}

	void EditorModule::RenderEditor()
	{
		if (!_editorRenderingEnabled)
		{
			return;
		}

		const std::shared_ptr<ImGuiRenderer> imGuiRenderer = _modules->rendering->ImGuiRender().lock();
		if (imGuiRenderer == nullptr) return;

		imGuiRenderer->Add([this]()
		{
			_menuBar->Draw();

			DrawWindows();
		});
	}

	void EditorModule::DrawWindows()
	{
		for (auto it = _windows.begin(); it != _windows.end(); ++it)
		{
			if (!(*it)->Visible)
			{
				continue;
			}

			(*it)->Draw();
		}
	}
} // GEngineCore