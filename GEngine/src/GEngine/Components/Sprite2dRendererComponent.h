//
// Created by guillem on 12/1/25.
//

#ifndef SPRITE2DRENDERERCOMPONENT_H
#define SPRITE2DRENDERERCOMPONENT_H

#include <memory>

#include "Component.h"

namespace GEngine
{
	class Entity;
	class SpriteResource;

	class Sprite2dRendererComponent final : public Component
	{
		REGISTER_COMPONENT(Sprite2dRendererComponent)

	public:
		explicit Sprite2dRendererComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity);

		void OnTick() override;

		void SetRenderLayer(std::int32_t layer) const;
		void SetSprite(const std::weak_ptr<SpriteResource> &sprite) const;
		void SetSpriteIndex(int index) const;
		void SetFlippedX(bool flippedX) const;

		[[nodiscard]] std::weak_ptr<SpriteResource> GetSprite() const;
		[[nodiscard]] int GetSpriteIndex() const;

	private:
		std::shared_ptr<Property<std::int32_t>> _renderLayer;
		std::shared_ptr<Property<std::weak_ptr<SpriteResource>>> _spriteResource;
		std::shared_ptr<Property<std::int32_t>> _spriteIndex;
		std::shared_ptr<Property<bool>> _isFlippedX;
	};

} // GEngine

#endif //SPRITE2DRENDERERCOMPONENT_H
