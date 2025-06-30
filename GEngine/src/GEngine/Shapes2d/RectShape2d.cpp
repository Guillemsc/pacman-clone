//
// Created by guillem on 6/30/25.
//

#include "RectShape2d.h"

#include "GEngine/Extensions/Vec2Extensions.h"

namespace GEngine
{
	RectShape2d::RectShape2d()
	{
		_size = _properties.Register<glm::vec2>("Size", { 10, 10 });
	}

	void RectShape2d::SetSize(const glm::vec2 &size) const
	{
		_size->SetValue(size);
	}

	glm::vec2 RectShape2d::GetSize() const
	{
		return _size->GetValue();
	}
} // GEngine