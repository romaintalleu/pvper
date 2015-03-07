#pragma once
#include <priv/base.h>

namespace pvper {
namespace cache {
	namespace data {
		static inline void
		clean() { __asm__ volatile("mcr p15, 0, %0, c7, c10, 0" : : "r" (0) : "memory"); }

		static inline void
		invalidate() { __asm__ volatile("mcr p15, 0, %0, c7, c6,  0" : : "r" (0) : "memory"); }
	}

	namespace instruction {
		static inline void
		flushBranchTarget() { __asm__ volatile("mcr p15, 0, %0, c7, c5,  6" : : "r" (0) : "memory"); }

		static inline void
		flushPrefetch() { __asm__ volatile("mcr p15, 0, %0, c7, c5,  4" : : "r" (0) : "memory"); }

		static inline void
		invalidate() { __asm__ volatile("mcr p15, 0, %0, c7, c5,  0" : : "r" (0) : "memory"); }
	}
}

namespace critical {
	void
	enter(void);

	void
	leave(void);

	const uint32_t
	level(void);
}

namespace barrier {
	namespace data {
		static inline void
		mem() { __asm__ volatile("mcr p15, 0, %0, c7, c10, 5" : : "r" (0) : "memory"); }

		static inline void
		sync() { __asm__ volatile("mcr p15, 0, %0, c7, c10, 4" : : "r" (0) : "memory"); }
	}

	namespace instruction {
		static inline void
		mem() { pvper::cache::instruction::flushPrefetch(); }

		static inline void
		sync() { pvper::cache::instruction::flushPrefetch(); }
	}
}

namespace interrupts {
	static inline void
	disable() { __asm__ volatile("cpsid i"); }
	
	static inline void
	enable() { __asm__ volatile("cpsie i"); }
}
}