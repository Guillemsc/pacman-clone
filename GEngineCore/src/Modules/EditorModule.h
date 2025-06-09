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
		std::weak_ptr<GEngineObject> GetSelectedObject() const;

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

	template<class T>
	void EditorModule::RegisterWindow()
	{
		static_assert(std::is_base_of_v<EditorWindow, T>, "T is not derived from EditorWindow");

		std::shared_ptr<T> window = std::make_shared<T>(_app);

		_windows.push_back(window);
	}
}

#endif //EDITORMODULE_H
