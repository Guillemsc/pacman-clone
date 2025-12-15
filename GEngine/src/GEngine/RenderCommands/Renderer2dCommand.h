//
// Created by guillem on 12/15/25.
//

#ifndef RENDERCOMMAND_H
#define RENDERCOMMAND_H

#include <memory>

#include "GEngine/Colors/Color01.h"
#include "glm/vec2.hpp"

#include "GEngine/Raylib/RaylibWrapper.h"
#include "GEngine/Resources/TiledMapResource.h"

namespace GEngine
{
	class TiledMapResource;

	enum class Renderer2dCommandType
	{
		TEXTURE,
		RECT,
		TILED_LAYER,
	};

	struct TextureRenderer2dCommand
	{
		Texture2D texture;
		rlRectangle source;
		glm::vec2 position;
		float rotationRadians;
		glm::vec2 scale;
		Color01 color;
	};

	struct RectRenderer2dCommand
	{
		glm::vec2 position;
		float rotationRadians;
		glm::vec2 scale;
		glm::vec2 size;
		Color01 color;
	};

	struct TiledLayerRenderer2dCommand
	{
		TiledMapResource* tiledMapResource;
		int layerIndex;
		glm::vec2 position;
		float rotationRadians;
		glm::vec2 scale;
	};

	struct Renderer2dCommand
	{
		Renderer2dCommandType type;

		union
		{
			TextureRenderer2dCommand texture;
			RectRenderer2dCommand rect;
			TiledLayerRenderer2dCommand tiledLayer;
		};
	};
}

#endif //RENDERCOMMAND_H
