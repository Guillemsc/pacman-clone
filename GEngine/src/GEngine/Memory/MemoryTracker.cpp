//
// Created by guillem on 12/14/25.
//

#include "MemoryTracker.h"

#include <cstdlib>
#include <new>

std::atomic<size_t> GEngine::MemoryTracker::totalAllocated = {0};
std::atomic<size_t> GEngine::MemoryTracker::totalFreed = {0};
bool GEngine::MemoryTracker::isTracking = true;

void* operator new(const std::size_t size)
{
	// Allocate extra space to store size
	const std::size_t totalSize = size + sizeof(std::size_t);
	void* raw = std::malloc(totalSize);
	if (!raw) throw std::bad_alloc();

	// Store size at the beginning
	*static_cast<std::size_t*>(raw) = size;

	if (GEngine::MemoryTracker::isTracking)
	{
		GEngine::MemoryTracker::totalAllocated += size;
	}

	// Return pointer after the size header
	return static_cast<char*>(raw) + sizeof(std::size_t);
}

void operator delete(void* ptr) noexcept
{
	if (!ptr) return;

	// Go back to header
	void* raw = static_cast<char*>(ptr) - sizeof(std::size_t);
	const std::size_t size = *static_cast<std::size_t*>(raw);

	if (GEngine::MemoryTracker::isTracking)
	{
		GEngine::MemoryTracker::totalFreed += size;
	}

	std::free(raw);
}

void operator delete(void* ptr, std::size_t) noexcept
{
	operator delete(ptr);
}

void* operator new[](const std::size_t size)
{
	const std::size_t totalSize = size + sizeof(std::size_t);
	void* raw = std::malloc(totalSize);
	if (!raw) throw std::bad_alloc();

	*static_cast<std::size_t*>(raw) = size;
	GEngine::MemoryTracker::totalAllocated += size;

	return static_cast<char*>(raw) + sizeof(std::size_t);
}

void operator delete[](void* ptr) noexcept
{
	if (!ptr) return;

	void* raw = static_cast<char*>(ptr) - sizeof(std::size_t);
	const std::size_t size = *static_cast<std::size_t*>(raw);

	GEngine::MemoryTracker::totalFreed += size;
	std::free(raw);
}

void operator delete[](void* ptr, std::size_t) noexcept
{
	operator delete[](ptr);
}