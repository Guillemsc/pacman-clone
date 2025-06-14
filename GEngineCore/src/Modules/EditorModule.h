//
// Created by guillem on 6/9/25.
//

#ifndef EDITORMODULE_H
#define EDITORMODULE_H

#include <functional>
#include <memory>
#include <vector>

namespace GEngineCore
{
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

		void SetSelectedObject(const std::weak_ptr<GEngineObject> &object);
		[[nodiscard]] std::weak_ptr<GEngineObject> GetSelectedObject() const;
		template<typename T>
		bool IsSelectedObject(std::weak_ptr<T> object);

	private:
		void DrawEditor();
		void DrawWindows();

		template <class T>
		void RegisterWindow();

	private:
		std::weak_ptr<GEngineCoreApplication> _app;

		std::vector<std::shared_ptr<EditorWindow>> _windows;

		std::weak_ptr<GEngineObject> _selectedObject;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

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
