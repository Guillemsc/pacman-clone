//
// Created by guillem on 6/10/25.
//

#ifndef RAYLIBEXTENSIONS_H
#define RAYLIBEXTENSIONS_H
#include "raylib.h"

namespace GEngineCore
{
	class RayLibExtensions
	{
	public:
		static void DrawTextureEx(const Texture2D &texture, const Vector2 position, const float rotation, const Vector2 scale, const Color tint)
		{
			const Rectangle source = { 0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height) };
			const Rectangle dest = { position.x, position.y, static_cast<float>(texture.width) * scale.x, static_cast<float>(texture.height) * scale.y };
			constexpr Vector2 origin = { 0.0f, 0.0f };

			DrawTexturePro(texture, source, dest, origin, rotation, tint);
		}
	};
}

#endif //RAYLIBEXTENSIONS_H
