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
			Clear();
		}

		void SetWhenReset(const std::function<void(T*)>& whenReset)
		{
			_whenReset = whenReset;
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
				if (_whenReset)
				{
					_whenReset(ptr);
				}

				_objects.push(ptr); // Return to pool
			});
		}

		void Clear()
		{
			while (!_objects.empty())
			{
				delete _objects.top();
				_objects.pop();
			}
		}

	private:
		std::stack<T*> _objects;
		std::function<void(T*)> _whenReset;
	};
}

#endif //OBJECTPOOL_H
