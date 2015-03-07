#include <priv/hw/Sync.h>
#include <priv/base.h>

static volatile uint32_t _criticalLevel = 0;
static volatile bool _wereEnabled;

namespace pvper {
namespace critical {
	void enter(void)
	{
		uint32_t flags;
		__asm__ volatile("mrs %0, cpsr" : "=r" (flags));

		pvper::interrupts::disable();

		if (_criticalLevel++ == 0)
		{
			_wereEnabled = flags & 0x80 ? false : true;
		}

		pvper::barrier::data::mem();
	}

	void leave(void)
	{
		pvper::barrier::data::mem();

		assert(_criticalLevel > 0);
		if (--_criticalLevel == 0)
		{
			if (_wereEnabled)
				pvper::interrupts::enable();
		}
	}

	const uint32_t level(void)
	{
		return _criticalLevel;
	}
}
}