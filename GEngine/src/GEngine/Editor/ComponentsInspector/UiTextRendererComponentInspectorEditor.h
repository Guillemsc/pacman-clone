//
// Created by guillem on 12/17/25.
//

#ifndef UITEXTRENDERERCOMPONENTINSPECTOREDITOR_H
#define UITEXTRENDERERCOMPONENTINSPECTOREDITOR_H

#include "ComponentInspectorEditor.h"
#include "GEngine/Components/UiTextRendererComponent.h"

namespace GEngine
{
	class UiTextRendererComponentInspectorEditor final : public ComponentInspectorEditor<UiTextRendererComponent>
	{
	public:
		using ComponentInspectorEditor::ComponentInspectorEditor;

		void DrawSpecific(const std::shared_ptr<UiTextRendererComponent>& inspect) override;

	private:
		static bool DrawToolbarButton(const char* label, bool selected);
	};
}

#endif //UITEXTRENDERERCOMPONENTINSPECTOREDITOR_H
