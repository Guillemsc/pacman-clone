//
// Created by guillem on 6/28/25.
//

#ifndef TIMESOURCE_H
#define TIMESOURCE_H

namespace GEngine
{
	class ITimeSource
	{
	public:
		virtual double GetTimeSeconds() const = 0;
	};
}

#endif //TIMESOURCE_H
