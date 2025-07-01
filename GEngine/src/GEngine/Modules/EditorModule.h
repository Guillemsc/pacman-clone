//
// Created by guillem on 6/9/25.
//

#ifndef EDITORMODULE_H
#define EDITORMODULE_H

#include <functional>
#include <memory>
#include <vector>
#include <typeindex>

namespace GEngine
{
	class IPropertyDrawerEditor;
	class IProperty;
	class MenuBarEditor;
	class GEngineObject;
	class Entity;
	class EditorWindow;
	class GEngineCoreApplication;

	class EditorModule
	{
	public:
		void Init(const std::weak_ptr<GEngineCoreApplication>& app);
		void Tick();
		void Dispose();

		template<class TPropertyDrawer, class TSerializedProperty>
		void RegisterPropertyDrawer();

		void DrawProperty(IProperty* property) const;
		void DrawObject(const GEngineObject* gEngineObject) const;

		void SetSelectedObject(const std::weak_ptr<GEngineObject> &object);
		[[nodiscard]] std::weak_ptr<GEngineObject> GetSelectedObject() const;
		template<typename T>
		bool IsSelectedObject(std::weak_ptr<T> object);

	private:
		void RenderEditor();
		void DrawWindows();

		template <class T>
		void RegisterWindow();

	private:
		std::weak_ptr<GEngineCoreApplication> _app;

		bool _editorRenderingEnabled = true;

		std::unordered_map<std::type_index, std::shared_ptr<IPropertyDrawerEditor>> _propertyDrawers;

		std::shared_ptr<MenuBarEditor> _menuBar;
		std::vector<std::shared_ptr<EditorWindow>> _windows;

		std::weak_ptr<GEngineObject> _selectedObject;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class TPropertyDrawer, class TSerializedProperty>
	void EditorModule::RegisterPropertyDrawer()
	{
		static_assert(std::is_base_of_v<IPropertyDrawerEditor, TPropertyDrawer>, "TPropertyDrawer is not derived from PropertyDrawerEditor");
		static_assert(std::is_base_of_v<IProperty, TSerializedProperty>, "TSerializedProperty is not derived from ISerializedProperty");

		const std::type_index typeIndex = typeid(TSerializedProperty);

		_propertyDrawers[typeIndex] = std::make_shared<TPropertyDrawer>();
	}

	template <typename T>
	bool EditorModule::IsSelectedObject(std::weak_ptr<T> object)
	{
		static_assert(std::is_base_of_v<GEngineObject, T>, "T is not derived from GEngineObject");

		const std::shared_ptr<GEngineObject> selectedObject = _selectedObject.lock();
		if (!selectedObject) return false;

		const std::shared_ptr<GEngineObject> sharedDerived = std::static_pointer_cast<GEngineObject>(object);
		if (!sharedDerived) return false;

		return selectedObject.get() == sharedDerived.get();
	}

	template<class T>
	void EditorModule::RegisterWindow()
	{
		static_assert(std::is_base_of_v<EditorWindow, T>, "T is not derived from EditorWindow");

		std::shared_ptr<T> window = std::make_shared<T>(_app);

		_windows.push_back(window);
	}
}

#endif //EDITORMODULE_H
