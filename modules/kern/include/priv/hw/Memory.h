#pragma once
#include <priv/base.h>

namespace pvper {
namespace hw {
	class MemoryManager {
	public:
		static MemoryManager&
		shared();

		void*
		alloc(size_t size);
		
		void
		dealloc(void* zone);

	private:
		MemoryManager();
		~MemoryManager();

		void *_nextBlock;
	};
}
}
