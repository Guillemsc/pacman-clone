//
// Created by guillem on 6/9/25.
//

#ifndef GENGINEOBJECT_H
#define GENGINEOBJECT_H

#include "GEngineObjectType.h"

namespace GEngineCore
{
	class GEngineObject
	{
	public:
		virtual ~GEngineObject() = default;

		virtual GEngineObjectType GetObjectType() = 0;
	};
}

#endif //GENGINEOBJECT_H
