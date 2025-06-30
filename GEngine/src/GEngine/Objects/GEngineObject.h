//
// Created by guillem on 6/9/25.
//

#ifndef GENGINEOBJECT_H
#define GENGINEOBJECT_H

#include "GEngineObjectType.h"
#include "GEngine/SerializedProperties/PropertiesContainer.h"

namespace GEngine
{
	class GEngineObject
	{
	public:
		virtual ~GEngineObject() = default;

		virtual GEngineObjectType GetObjectType()
		{
			return GEngineObjectType::UNKNOWN;
		};

		const PropertiesContainer& GetProperties() const
		{
			return _properties;
		}

	protected:
		PropertiesContainer _properties;
	};
}

#endif //GENGINEOBJECT_H
