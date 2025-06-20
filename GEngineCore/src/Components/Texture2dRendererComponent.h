//
// Created by guillem on 6/9/25.
//

#ifndef TEXTURERENDERER2DCOMPONENT_H
#define TEXTURERENDERER2DCOMPONENT_H

#include <memory>

#include "Component.h"

namespace GEngineCore
{
	class TextureResource;
	class Entity;

	class Texture2dRendererComponent final : public Component
	{
	public:
		explicit Texture2dRendererComponent(const std::weak_ptr<Entity> &entity);

		static ComponentType GetTypeStatic() { return ComponentType::TEXTURE_2D_RENDERER; }
		ComponentType GetType() override { return GetTypeStatic(); }
		const char* GetTypeName() override { return "Texture2dRenderer"; }

		void OnTick() override;

		void SetTexture(const std::weak_ptr<TextureResource> &texture);

	private:
		std::weak_ptr<TextureResource> _texturePtr;
	};
}

#endif //TEXTURERENDERER2DCOMPONENT_H
