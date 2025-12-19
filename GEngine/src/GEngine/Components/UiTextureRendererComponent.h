//
// Created by guillem on 12/19/25.
//

#ifndef UITEXTURERENDERERCOMPONENT_H
#define UITEXTURERENDERERCOMPONENT_H

#include "Component.h"
#include "GEngine/Colors/Color01.h"

namespace GEngine
{
	class TextureResource;

	class UiTextureRendererComponent final : public Component
	{
		REGISTER_COMPONENT(UiTextureRendererComponent)

	public:
		UiTextureRendererComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity);

		void OnTick() override;

		void SetPreserveAspectRatio(bool preserveAspectRatio) const;
		void SetTexture(const std::weak_ptr<TextureResource> &texture);

	private:
		std::weak_ptr<TextureResource> _textureResource;
		std::shared_ptr<Property<bool>> _preserveAspectRatio;
		std::shared_ptr<Property<Color01>> _color;
	};
}

#endif //UITEXTURERENDERERCOMPONENT_H
