//
// Created by guillem on 6/7/25.
//

#ifndef EVENTBUSES_H
#define EVENTBUSES_H

#include "EventBus.h"

namespace GEngineCore
{
	struct EntityDestroyedEvent;

	class EventBuses
	{
	public:
		EventBuses(): EntityDestroyed()
		{
		}

		const EventBus<EntityDestroyedEvent> EntityDestroyed;
	};
}

#endif //EVENTBUSES_H
