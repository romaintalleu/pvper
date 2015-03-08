#include <priv/hw/Memory.h>
#include <priv/hw/Serial.h>

#define HEAP_BASE 0x40000

namespace pvper {
namespace hw {
	MemoryManager MemoryManager::instance;

	/*static*/ MemoryManager&
	MemoryManager::shared()
	{
		return instance;
	}

	MemoryManager::MemoryManager() :
	_nextBlock((uint8_t*)HEAP_BASE)
	{ }

	MemoryManager::~MemoryManager()
	{ }

	void*
	MemoryManager::alloc(const size_t size)
	{
		assert(size != 0);
		void* zone = _nextBlock;
		_nextBlock = ((uint8_t*)_nextBlock + (size < 4 ? 4 : size));
		pvper::hw::Serial::shared() << "Memory manager " << this << " allocated memory zone of " << size << " bytes at " << zone << ", next block starts at " << _nextBlock << ".\n";
		return zone;
	}

	void
	MemoryManager::dealloc(void* zone)
	{
		assert(zone != nullptr);
		pvper::hw::Serial::shared() << "Deallocating memory zone at " << zone << ".\n";
		return;
	}
}
}

void* operator new(size_t size) noexcept
{ return pvper::hw::MemoryManager::shared().alloc(size); }

void operator delete(void *zone) noexcept
{ pvper::hw::MemoryManager::shared().dealloc(zone); }

void* operator new[](size_t size) noexcept
{ return operator new(size); }

void operator delete[](void* zone) noexcept
{ return operator delete(zone); }

