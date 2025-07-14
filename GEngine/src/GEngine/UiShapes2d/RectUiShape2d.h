//
// Created by guillem on 7/12/25.
//

#ifndef RECTUISHAPE2D_H
#define RECTUISHAPE2D_H

#include "UiShape2d.h"

namespace GEngine
{
	class RectUiShape2d final : public UiShape2d
	{
	public:
		constexpr const char *GetObjectTypeName() const override { return "RectUiShape2d"; };
	};
}

#endif //RECTUISHAPE2D_H
