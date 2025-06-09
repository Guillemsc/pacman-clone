//
// Created by guillem on 6/9/25.
//

#ifndef TEXTURERENDERER2DCOMPONENT_H
#define TEXTURERENDERER2DCOMPONENT_H

#include <memory>

#include "Component.h"

namespace GEngineCore
{
	class Entity;

	class TextureRenderer2dComponent : public Component
	{
	public:
		explicit TextureRenderer2dComponent(const std::weak_ptr<Entity> &entity);

		static ComponentType GetTypeStatic() { return ComponentType::TEXTURE_RENDERER_2D; }
		ComponentType GetType() override { return GetTypeStatic(); }
		const char* GetTypeName() override { return "TextureRenderer2d"; }
	};
}

#endif //TEXTURERENDERER2DCOMPONENT_H
