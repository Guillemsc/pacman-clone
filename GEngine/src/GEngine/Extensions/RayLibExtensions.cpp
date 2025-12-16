//
// Created by guillem on 6/10/25.
//

#include "RayLibExtensions.h"

#include "rlgl.h"

namespace GEngine
{
	void RayLibExtensions::DrawTextCodepointExtension(
		const Font &font,
		const int codepoint,
		const Vector2 position,
		const float rotation,
		const float fontSize,
		const Color tint
		)
	{
		rlPushMatrix();

		rlTranslatef(position.x, position.y, 0.0f);
		rlRotatef(rotation, 0.0f, 0.0f, 1.0f);

		DrawTextCodepoint(font, codepoint, (Vector2){ 0.0f, 0.0f }, fontSize, tint);

		rlPopMatrix();
	}
}
