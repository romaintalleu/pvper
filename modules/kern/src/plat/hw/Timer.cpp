#include <priv/hw/MMIO.h>
#include <priv/hw/Timer.h>

namespace pvper {
namespace hw {
	void
	Timer::sleep(uint32_t duration) {
		uint32_t currentCount = pvper::hw::MMIO::read(ARM_SYSTIMER_CLO);
		uint32_t endCount = currentCount + duration;

		while (currentCount < endCount) {
			currentCount = pvper::hw::MMIO::read(ARM_SYSTIMER_CLO);
		}
	}
}}
