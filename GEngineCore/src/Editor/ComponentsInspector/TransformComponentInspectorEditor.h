//
// Created by guillem on 6/9/25.
//

#ifndef TRANSFORMCOMPONENTINSPECTOREDITOR_H
#define TRANSFORMCOMPONENTINSPECTOREDITOR_H
#include "ComponentInspectorEditor.h"
#include "Components/TransformComponent.h"

namespace GEngineCore
{
	class TransformComponentInspectorEditor : public ComponentInspectorEditor<TransformComponent>
	{
		void DrawSpecific(const std::shared_ptr<TransformComponent>& inspect) override;
	};
}

#endif //TRANSFORMCOMPONENTINSPECTOREDITOR_H
