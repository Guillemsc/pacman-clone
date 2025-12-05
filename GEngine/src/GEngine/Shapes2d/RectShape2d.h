//
// Created by guillem on 6/30/25.
//

#ifndef RECTSHAPE2D_H
#define RECTSHAPE2D_H

#include "Shape2d.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	class RectShape2d final : public Shape2d
	{
	public:
		RectShape2d();

		constexpr const char* GetObjectTypeName() const override { return "RectShape2d"; };

		void SetSize(const glm::vec2& size) const;
		glm::vec2 GetSize() const;

	private:
		std::shared_ptr<Property<glm::vec2>> _size;
	};
}

#endif //RECTSHAPE2D_H
