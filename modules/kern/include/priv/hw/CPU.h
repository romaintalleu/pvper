#pragma once
#include <priv/base.h>

namespace pvper {
namespace hw {
namespace CPU {
	
	static inline void delay(int32_t count)
	{ for (int register _=0;_<count;_++){__asm__ volatile("nop");} }
	
}
}
}
