//
// Created by guillem on 6/9/25.
//

#ifndef TEXTURERENDERER2DCOMPONENT_H
#define TEXTURERENDERER2DCOMPONENT_H

#include <memory>

#include "Component.h"

namespace GEngine
{
	class TextureResource;
	class Entity;

	class Texture2dRendererComponent final : public Component
	{
		DECLARE_COMPONENT(Texture2dRendererComponent)

	public:
		explicit Texture2dRendererComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity);

		void OnTick() override;

		void SetTexture(const std::weak_ptr<TextureResource> &texture);

	private:
		std::weak_ptr<TextureResource> _textureResource;
	};
}

#endif //TEXTURERENDERER2DCOMPONENT_H
