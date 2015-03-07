#pragma once
#include <stddef.h>
#include <stdint.h>

namespace pvper {
namespace hw {
namespace MMIO{
	
	static inline uint32_t read(uint32_t reg)
	{ return *(volatile uint32_t *)reg; }

	static inline void write(uint32_t reg, uint32_t data)
	{ *(volatile uint32_t *)reg = data; }
	
}
}
}
