#pragma once
#include <priv/base.h>

#define GPIO_PIN_COUNT 54

namespace pvper {
namespace hw {
	class Timer {

	public:
		static void
		sleep(uint32_t duration);
	};
}}
