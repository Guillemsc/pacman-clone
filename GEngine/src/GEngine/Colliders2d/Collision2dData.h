//
// Created by guillem on 12/3/25.
//

#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H

#include <memory>

#include "Collider2d.h"

namespace GEngine
{
	struct Collision2dData
	{
		std::weak_ptr<Collider2d> owner;
		std::weak_ptr<Collider2d> collider;
	};
}

#endif //COLLISIONDATA_H
