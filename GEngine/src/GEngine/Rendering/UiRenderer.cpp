//
// Created by guillem on 7/1/25.
//

#include "UiRenderer.h"

#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Extensions/Color01Extensions.h"
#include "GEngine/Extensions/RayLibExtensions.h"
#include "GEngine/Extensions/Vec4Extensions.h"
#include "GEngine/Modules/WindowModule.h"
#include "glm/detail/func_trigonometric.inl"
#include "GEngine/Raylib/RaylibWrapper.h"

namespace GEngine
{
	UiRenderer::UiRenderer(GEngineCoreModules* modules)
		: _modules(modules)
	{

	}

	void UiRenderer::Render()
	{
		for (auto it = _queue.begin(); it != _queue.end(); ++it)
		{
			const std::vector<UiRendererCommand>& commands = it->second;

			for (auto commandIt = commands.begin(); commandIt != commands.end(); ++commandIt)
			{
				const UiRendererCommand& command = *commandIt;
				RenderCommand(command);
			}

			it->second.clear();
		}
	}

	void UiRenderer::AddTexture(
		const std::int32_t layer,
		const Texture2D& texture,
		const glm::vec2 &position,
		const float rotationRadians,
		const glm::vec2 &size,
		const glm::vec2 &center,
		const Color01 &color
		)
	{
		AddCommand(
			layer,
			UiRendererCommand {
				.type = UiRendererCommandType::TEXTURE,
				.texture = {
					texture,
					position,
					rotationRadians,
					size,
					center,
					color
				}
			});
	}

	void UiRenderer::AddRect(
		const std::int32_t layer,
		const glm::vec2 &position,
		const float rotationRadians,
		const glm::vec2 &size,
		const glm::vec2& center,
		const Color01 &color
		)
	{
		AddCommand(
			layer,
			UiRendererCommand {
				.type = UiRendererCommandType::RECT,
				.rect = {
					position,
					rotationRadians,
					size,
					center,
					color
				}
			});
	}

	void UiRenderer::AddText(
		const std::int32_t layer,
		FontResource *font,
		const std::string_view &text,
		const float textScale,
		const glm::vec2 &position,
		const float rotationRadians,
		const glm::vec2 &size,
		const glm::vec2 &pivot,
		const float wordSpacing,
		const Color01 &color,
		const HorizontalTextAlign horizontalAlign,
		const VerticalTextAlign verticalAlign
		)
	{
		AddCommand(
			layer,
			UiRendererCommand {
				.type = UiRendererCommandType::TEXT,
				.text = {
					font,
					text,
					textScale,
					position,
					rotationRadians,
					size,
					pivot,
					wordSpacing,
					color,
					horizontalAlign,
					verticalAlign
				}
			});
	}

	glm::vec2 UiRenderer::PositionToRenderPosition(const glm::vec2 &position) const
	{
		const glm::vec2 windowSize = _modules->window->GetWindowSize();

		const float newPositionY = windowSize.y - position.y;

		return { position.x, newPositionY };
	}

	glm::vec2 UiRenderer::PivotToRenderPivot(const glm::vec2 &pivot) const
	{
		const glm::vec2 renderPivot = { pivot.x, 1 - pivot.y };
		return renderPivot;
	}

	glm::vec4 UiRenderer::RectToRenderRect(const glm::vec4 &rect) const
	{
		const glm::vec2 windowSize = _modules->window->GetWindowSize();
		const glm::vec2 rectSize = Vec4Extensions::GetSize(rect);

		glm::vec4 newRect = rect;

		newRect.y = windowSize.y - rect.y - rectSize.y;
		newRect.w = windowSize.y - rect.y;

		return newRect;
	}

	float UiRenderer::RotationToRenderRotation(const float rotation)
	{
		return -rotation;
	}

	void UiRenderer::AddCommand(const std::int32_t layer, const UiRendererCommand &command)
	{
		_queue[layer].push_back(command);
	}

	void UiRenderer::RenderCommand(const UiRendererCommand &command)
	{
		switch (command.type)
		{
			case UiRendererCommandType::TEXTURE:
			{
				RenderTextureCommand(command.texture);
				break;
			}

			case UiRendererCommandType::RECT:
			{
				RenderRectCommand(command.rect);
				break;
			}

			case UiRendererCommandType::TEXT:
			{
				RenderTextCommand(command.text);
				break;
			}
		}
	}

	void UiRenderer::RenderTextureCommand(const TextureUiRendererCommand &command) const
	{
		const glm::vec2 renderPosition = PositionToRenderPosition(command.position);
		const rlRectangle rect = { renderPosition.x, renderPosition.y, command.size.x, command.size.y};
		const float rotationDegrees = RotationToRenderRotation(glm::degrees(command.rotationRadians));
		const glm::vec2 renderPivot = PivotToRenderPivot(command.pivot);
		const glm::vec2 center = { command.size.x * renderPivot.x, command.size.y * renderPivot.y };
		const Color raylibColor = Color01Extensions::ToRaylibColor(command.color);

		const rlRectangle sourceRect = rlRectangle{ 0, 0, static_cast<float>(command.texture.width), static_cast<float>(command.texture.height) };

		DrawTexturePro(command.texture, sourceRect, rect, { center.x, center.y }, rotationDegrees, raylibColor);
	}

	void UiRenderer::RenderRectCommand(const RectUiRendererCommand &command) const
	{
		const glm::vec2 renderPosition = PositionToRenderPosition(command.position);
		const rlRectangle rect = { renderPosition.x, renderPosition.y, command.size.x, command.size.y};
		const float rotationDegrees = RotationToRenderRotation(glm::degrees(command.rotationRadians));
		const glm::vec2 renderPivot = PivotToRenderPivot(command.pivot);
		const glm::vec2 center = { command.size.x * renderPivot.x, command.size.y * renderPivot.y };
		const Color raylibColor = Color01Extensions::ToRaylibColor(command.color);

		DrawRectanglePro(rect, { center.x, center.y }, rotationDegrees, raylibColor);
	}

	void UiRenderer::RenderTextCommand(const TextUiRendererCommand &command)
	{
		constexpr float charSpacing = 2.0f;

		Font rawFont;

		if (command.font == nullptr)
		{
			rawFont = GetFontDefault();
		}
		else
		{
			rawFont = command.font->GetRawFont();
		}

		const glm::vec2 renderPosition = PositionToRenderPosition(command.position);
		const glm::vec2 renderPivot = PivotToRenderPivot(command.pivot);
		const glm::vec2 center = { command.size.x * renderPivot.x, command.size.y * renderPivot.y };
		const float renderRotation = RotationToRenderRotation(command.rotationRadians);
		const float renderRotationDegrees = glm::degrees(renderRotation);
		const Color raylibColor = Color01Extensions::ToRaylibColor(command.color);

		const char* text = command.text.data();
		const int textLength = TextLength(text);

		bool wordWrap = command.horizontalAlign != HorizontalTextAlign::NO_WORD_WRAP;

		// Offset to next character to draw
		glm::vec2 charRenderOffset = glm::vec2(0.0f);

		enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
		int renderState = wordWrap ? MEASURE_STATE : DRAW_STATE;

		int currentStartLine = -1; // Index where to begin drawing (where a line begins)
		int currentEndLine = -1; // Index where to stop drawing (where a line ends)
		float currentLineWidth = 0.0f;

		for (int i = 0; i < textLength; i++)
		{
			// Get next codepoint from byte string and glyph index in font
			int codepointByteCount = 0;
			const int charCodepoint = GetCodepoint(&text[i], &codepointByteCount);
			int glyphIndex = GetGlyphIndex(rawFont, charCodepoint);

			// NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
			// but we need to draw all the bad bytes using the '?' symbol moving one byte
			const bool isBadByte = charCodepoint == 0x3f;
			if (isBadByte)
			{
				codepointByteCount = 1;
			}

			i += codepointByteCount - 1;

			float glyphWidth = 0;

			if (charCodepoint != '\n')
			{
				glyphWidth = rawFont.glyphs[glyphIndex].advanceX == 0 ?
					rawFont.recs[glyphIndex].width * command.textScale :
					rawFont.glyphs[glyphIndex].advanceX * command.textScale;

				const bool isLastCharacter = i + 1 >= textLength;
				if (!isLastCharacter)
				{
					glyphWidth = glyphWidth + charSpacing;
				}
			}

			// NOTE: When wordWrap is ON we first measure how much of the text we can draw before going outside the rec container
			// We store this info in startLine and endLine, then we change states, draw the text between those two variables
			// and change states again and again recursively until the end of the text (or until we get outside the container)
			// When wordWrap is OFF we don't need the measure state so we go to the drawing state immediately
			// and begin drawing on the next line before we can get outside the container
			if (renderState == MEASURE_STATE)
			{
				// TODO: There are multiple types of spaces in UNICODE, maybe it's a good idea to add support for more
				// Ref: http://jkorpela.fi/chars/spaces.html
				const bool isSpaceCharacter = charCodepoint == ' ' || charCodepoint == '\t' || charCodepoint == '\n';
				if (isSpaceCharacter)
				{
					currentEndLine = i;
					currentLineWidth = charRenderOffset.x - charSpacing;
				}

				float testingLineWidth = charRenderOffset.x + glyphWidth;
				const bool characterGoesOutsideBounds = testingLineWidth > command.size.x;
				if (characterGoesOutsideBounds)
				{
					currentEndLine = currentEndLine < 1 ? i : currentEndLine;
					if (i == currentEndLine)
					{
						currentEndLine -= codepointByteCount;
					}

					if (currentStartLine + codepointByteCount == currentEndLine)
					{
						currentEndLine = i - codepointByteCount;
					}

					renderState = DRAW_STATE;
				}
				else if (i + 1 == textLength)
				{
					currentEndLine = i;
					currentLineWidth = testingLineWidth;
					renderState = DRAW_STATE;
				}
				else if (charCodepoint == '\n')
				{
					currentLineWidth = testingLineWidth;
					renderState = DRAW_STATE;
				}

				if (renderState == DRAW_STATE)
				{
					charRenderOffset.x = 0;
					i = currentStartLine;
					glyphWidth = 0;
				}
			}
			else
			{
				const bool charIsNewLine = charCodepoint == '\n';

				if (charIsNewLine)
				{
					// If we find a new line, we force line jump, even if it's the middle of a word
					if (!wordWrap)
					{
						charRenderOffset.y += (rawFont.baseSize + rawFont.baseSize / 2) * command.textScale;
						charRenderOffset.x = 0;
					}
				}
				else
				{
					// If we are outside the bounds, we force line jump, even if it's the middle of a word
					if (!wordWrap && ((charRenderOffset.x + glyphWidth) > command.size.x))
					{
						charRenderOffset.y += (rawFont.baseSize + rawFont.baseSize / 2) * command.textScale;
						charRenderOffset.x = 0;
					}

					// When text overflows rectangle height limit, just stop drawing
					const bool areWeExceedingHeightLimit = (charRenderOffset.y + rawFont.baseSize * command.textScale) > command.size.y;
					if (areWeExceedingHeightLimit) break;

					const float spaceLeftToFillRect = command.size.x - currentLineWidth;

					// Draw current character glyph
					const bool charCanBeRendered = charCodepoint != ' ' && charCodepoint != '\t';

					if (charCanBeRendered)
					{
						glm::vec2 finalCharRenderOffset = charRenderOffset - center;

						if (command.horizontalAlign == HorizontalTextAlign::RIGHT)
						{
							finalCharRenderOffset.x += spaceLeftToFillRect;
						}
						else if (command.horizontalAlign == HorizontalTextAlign::CENTER)
						{
							finalCharRenderOffset.x += spaceLeftToFillRect * 0.5f;
						}

						glm::vec2 finalPosition = MathExtensions::RotatePointAroundPivot(
							finalCharRenderOffset,
							{ 0, 0 },
							renderRotation
							);

						finalPosition += renderPosition;

						finalPosition.x = std::round(finalPosition.x);
						finalPosition.y = std::round(finalPosition.y);

						float charSize = static_cast<float>(rawFont.baseSize) *  command.textScale;

						RayLibExtensions::DrawTextCodepointExtension(
							rawFont,
							charCodepoint,
							{ finalPosition.x, finalPosition.y },
							renderRotationDegrees,
							charSize,
							raylibColor
							);
					}
				}

				const bool hasFinishedRenderingCurrentLine = wordWrap && i == currentEndLine;
				if (hasFinishedRenderingCurrentLine)
				{
					charRenderOffset.y += (rawFont.baseSize + rawFont.baseSize / 2) * command.textScale;
					charRenderOffset.x = 0;
					currentStartLine = currentEndLine;
					currentEndLine = -1;
					currentLineWidth = 0;
					glyphWidth = 0;

					renderState = MEASURE_STATE;
				}
			}

			// Avoid leading spaces
			if (charRenderOffset.x != 0 || (charCodepoint != ' '))
			{
				charRenderOffset.x += glyphWidth;
			}
		}
	}
} // GEngine