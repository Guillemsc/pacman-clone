//
// Created by guillem on 6/9/25.
//

#ifndef INSPECTOREDITORWINDOW_H
#define INSPECTOREDITORWINDOW_H

#include <vector>

#include "EditorWindow.h"
#include "Components/ComponentFactory.h"
#include "Components/ComponentType.h"
#include "Editor/Inspector/GEngineObjectInspectorEditor.h"
#include "Objects/GEngineObjectType.h"

namespace GEngineCore
{
	class IGEngineObjectInspectorEditor;
	class GEngineObject;

	class InspectorEditorWindow : public EditorWindow
	{
	public:
		explicit InspectorEditorWindow(const std::weak_ptr<GEngineCoreApplication> &app);

		void Draw() override;

	private:
		std::shared_ptr<IGEngineObjectInspectorEditor> GetInspectorEditor(GEngineObjectType gEngineObjectType);

		template<class TEditor, class TObject>
		void RegisterInspectorEditor();

	private:
		std::vector<std::shared_ptr<IGEngineObjectInspectorEditor>> _inspectorEditors;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class TEditor, class TObject>
	void InspectorEditorWindow::RegisterInspectorEditor()
	{
		static_assert(std::is_base_of_v<GEngineObjectInspectorEditor<TObject>, TEditor>, "TEditor is not derived from GEngineObjectInspectorEditor");
		static_assert(std::is_base_of_v<GEngineObject, TObject>, "TEditor is not derived from GEngineObject");

		const GEngineObjectType engineObjectType = TObject::GetObjectTypeStatic();
		const std::size_t objectIndex = static_cast<std::size_t>(engineObjectType);

		while (objectIndex + 1 > _inspectorEditors.size())
		{
			_inspectorEditors.push_back(nullptr);
		}

		_inspectorEditors[objectIndex] = std::make_shared<TEditor>();
	}
}

#endif //INSPECTOREDITORWINDOW_H
