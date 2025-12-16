//
// Created by guillem on 7/26/25.
//

#ifndef UITEXTRENDERERCOMPONENT_H
#define UITEXTRENDERERCOMPONENT_H

#include "Component.h"

namespace GEngine
{
	class FontResource;

	class UiTextRendererComponent final : public Component
	{
		REGISTER_COMPONENT(UiTextRendererComponent)

	public:
		explicit UiTextRendererComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity);

		void OnTick() override;

	private:
		std::weak_ptr<FontResource> _fontResource;

		std::string _text = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s";
	};
}

#endif //UITEXTRENDERERCOMPONENT_H
