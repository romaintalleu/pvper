#include <priv/hw/Memory.h>
#include <priv/hw/Serial.h>

#define HEAP_BASE 0x40000

namespace pvper {
namespace hw {
	/*static*/ MemoryManager&
	MemoryManager::shared()
	{
		static MemoryManager instance;
		return instance;
	}

	MemoryManager::MemoryManager() :
	_nextBlock((void*)HEAP_BASE)
	{
	}

	MemoryManager::~MemoryManager()
	{ }

	void*
	MemoryManager::alloc(const size_t size)
	{
		void* zone = _nextBlock;
		pvper::hw::Serial::shared().puts("Allocating memory zone of ");
		pvper::hw::Serial::shared().puts(todec(size, 0));
		pvper::hw::Serial::shared().puts(" bytes at 0x");
		pvper::hw::Serial::shared().puts(tohex((uint32_t)zone, 4));
		pvper::hw::Serial::shared().puts(".\r\n");
		_nextBlock = ((uint8_t*)_nextBlock + (size < 4 ? 4 : size));
		return zone;
	}

	void
	MemoryManager::dealloc(void* zone)
	{
		pvper::hw::Serial::shared().puts("Deallocating memory zone at 0x");
		pvper::hw::Serial::shared().puts(tohex((uint32_t)zone, 4));
		pvper::hw::Serial::shared().puts(".\r\n");
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

