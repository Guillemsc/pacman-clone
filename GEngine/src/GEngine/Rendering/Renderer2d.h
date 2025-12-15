//
// Created by guillem on 6/8/25.
//

#ifndef RENDERER2D_H
#define RENDERER2D_H

#include "LayeredRenderQueue.h"
#include "GEngine/Raylib/RaylibWrapper.h"
#include "GEngine/RenderCommands/Renderer2dCommand.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	struct Color01;
	class GEngineCoreModules;
}

namespace GEngine
{
	class Renderer2d
	{
	public:
		explicit Renderer2d(GEngineCoreModules* modules);

		void Render();

		void AddTexture(
			std::int32_t layer,
			const Texture2D& texture,
			const rlRectangle& source,
			const glm::vec2& position,
			float rotationRadians,
			const glm::vec2& scale,
			const Color01& color
			);

		void AddRect(
			std::int32_t layer,
			const glm::vec2& position,
			float rotationRadians,
			const glm::vec2& scale,
			const glm::vec2& size,
			const Color01& color
			);

		void AddTiledLayer(
			std::int32_t layer,
			TiledMapResource* tiledMapResource,
			int layerIndex,
			const glm::vec2& position,
			float rotationRadians,
			const glm::vec2& scale
		);

		static void DrawTexture(
			const Texture2D& texture,
			const rlRectangle& source,
			const glm::vec2& position,
			float rotationRadians,
			const glm::vec2& scale,
			const Color01& color
			);

		static glm::vec2 PositionToRenderPosition(const glm::vec2& position);
		static float RotationToRenderRotation(float rotation);

	private:
		void AddCommand(std::int32_t layer, const Renderer2dCommand& command);

		static void RenderCommand(const Renderer2dCommand& command);
		static void RenderTextureCommand(const TextureRenderer2dCommand& command);
		static void RenderRectCommand(const RectRenderer2dCommand& command);
		static void RenderTiledLayerCommand(const TiledLayerRenderer2dCommand& command);

	private:
		GEngineCoreModules* const _modules = nullptr;

		std::map<std::int32_t, std::vector<Renderer2dCommand>> _queue;
	};
}

#endif //RENDERER2D_H
