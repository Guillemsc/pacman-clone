//
// Created by guillem on 12/14/25.
//

#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

#include <functional>
#include <memory>
#include <stack>

namespace GEngine
{
	template<typename T>
	class ObjectPool
	{
	public:
		using Ptr = std::unique_ptr<T, std::function<void(T*)>>;

		~ObjectPool()
		{
			while (!_objects.empty())
			{
				delete _objects.top();
				_objects.pop();
			}
		}

		Ptr Acquire()
		{
			T* obj = nullptr;

			if (!_objects.empty())
			{
				obj = _objects.top();
				_objects.pop();
			}
			else
			{
				obj = new T();
			}

			// Wrap in unique_ptr with custom deleter
			return Ptr(obj, [this](T* ptr)
			{
				//Reset(ptr);       // Optional: reset object state
				_objects.push(ptr); // Return to pool
			});
		}

	private:
		std::stack<T*> _objects;
	};
}

#endif //OBJECTPOOL_H
