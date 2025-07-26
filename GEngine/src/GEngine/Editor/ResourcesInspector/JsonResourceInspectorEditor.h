//
// Created by guillem on 7/26/25.
//

#ifndef JSONRESOURCEINSPECTOREDITOR_H
#define JSONRESOURCEINSPECTOREDITOR_H

#include "ResourceInspectorEditor.h"
#include "GEngine/Resources/JsonResource.h"

namespace GEngine
{
	class JsonResourceInspectorEditor final : public ResourceInspectorEditor<JsonResource>
	{
	public:
		explicit JsonResourceInspectorEditor(const std::weak_ptr<GEngineCoreApplication> &app);

		void DrawSpecific(const std::shared_ptr<JsonResource> &inspect) override;
	};
}

#endif //JSONRESOURCEINSPECTOREDITOR_H
