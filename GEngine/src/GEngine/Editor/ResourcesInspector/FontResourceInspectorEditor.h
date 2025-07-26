//
// Created by guillem on 7/26/25.
//

#ifndef FONTRESOURCEINSPECTOREDITOR_H
#define FONTRESOURCEINSPECTOREDITOR_H

#include "ResourceInspectorEditor.h"
#include "GEngine/Resources/FontResource.h"

namespace GEngine
{
	class FontResourceInspectorEditor final : public ResourceInspectorEditor<FontResource>
	{
	public:
		explicit FontResourceInspectorEditor(const std::weak_ptr<GEngineCoreApplication> &app);

		void DrawSpecific(const std::shared_ptr<FontResource> &inspect) override;
	};
}

#endif //FONTRESOURCEINSPECTOREDITOR_H
