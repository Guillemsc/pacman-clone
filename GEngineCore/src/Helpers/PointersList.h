//
// Created by guillem on 6/7/25.
//

#ifndef POINTERSLIST_H
#define POINTERSLIST_H

#include <cstdint>
#include <vector>

#include "PointerRef.h"

namespace GEngineCore
{
	template<typename T>
	class PointersList
	{
	public:
		bool IsValid(const PointerRef& pointerRef) const
		{
			bool outsideBounds = pointerRef.index < 0 || pointerRef.index >= _pointers.size();

			if (outsideBounds)
			{
				return false;
			}

			const PointerRef& checkingPointerRef = _pointerRefs[pointerRef.index];

			if (checkingPointerRef.generation != pointerRef.generation)
			{
				return false;
			}

			return true;
		}

		PointerRef Reserve()
		{
			int generation = ++_generation;

			if (_freeIndices.size() <= 0)
			{
				int index = _pointers.size();

				PointerRef pointerRef(index, generation);

				_pointers.push_back(nullptr);
				_pointerRefs.push_back(pointerRef);
				return pointerRef;
			}

			int index = _freeIndices[0];
			_freeIndices.erase(_freeIndices.begin());

			PointerRef pointerRef(index, generation);

			_pointers[index] = nullptr;
			_pointerRefs[index] = pointerRef;

			return pointerRef;
		}

		void Set(const PointerRef& pointerRef, T* pointer)
		{
			bool isValid = IsValid(pointerRef);

			if (!isValid)
			{
				return;
			}

			_pointers[pointerRef.index] = pointer;
		}

		PointerRef Add(T* value)
		{
			PointerRef pointerRef = Reserve();
			Set(pointerRef, value);
			return pointerRef;
		}

		void Remove(const PointerRef& pointerRef)
		{
			bool isValid = IsValid(pointerRef);

			if (!isValid)
			{
				return;
			}

			_pointers[pointerRef.index] = nullptr;
			_pointerRefs[pointerRef.index] = PointerRef(-1, 0);

			_freeIndices.push_back(pointerRef.index);
		}

		T* Get(const PointerRef& pointerRef) const
		{
			bool isValid = IsValid(pointerRef);

			if (!isValid)
			{
				return nullptr;
			}

			T* pointer = _pointers[pointerRef.index];

			return pointer;
		}

	private:
		std::vector<T*> _pointers;
		std::vector<PointerRef> _pointerRefs;
		std::vector<int> _freeIndices;

		std::uint32_t _generation = 0;
	};
}

#endif //POINTERSLIST_H
