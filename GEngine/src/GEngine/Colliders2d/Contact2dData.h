//
// Created by guillem on 12/3/25.
//

#ifndef CONTACT2DDATA_H
#define CONTACT2DDATA_H

#include <memory>

#include "Collider2d.h"

namespace GEngine
{
	struct Contact2dData
	{
		std::weak_ptr<Entity> owner;
		std::weak_ptr<Entity> collider;
	};
}

#endif //CONTACT2DDATA_H
