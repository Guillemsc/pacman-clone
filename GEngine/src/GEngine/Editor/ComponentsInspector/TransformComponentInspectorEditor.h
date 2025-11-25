//
// Created by guillem on 6/9/25.
//

#ifndef TRANSFORMCOMPONENTINSPECTOREDITOR_H
#define TRANSFORMCOMPONENTINSPECTOREDITOR_H

#include "ComponentInspectorEditor.h"
#include "GEngine/Components/TransformComponent.h"

namespace GEngine
{
	class TransformComponentInspectorEditor final : public ComponentInspectorEditor<TransformComponent>
	{
	public:
		explicit TransformComponentInspectorEditor(GEngineCoreModules* modules);

		void DrawSpecific(const std::shared_ptr<TransformComponent>& inspect) override;
	};
}

#endif //TRANSFORMCOMPONENTINSPECTOREDITOR_H
