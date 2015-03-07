#pragma once
#include <priv/base.h>

namespace pvper {
namespace hw {

	enum GpioMode {
		GpioModeUnknown,
		GpioModeInput,
		GpioModeOutput,
		GpioModeInputPullUp,
		GpioModeInputPullDown,
		GpioModeAltFn0,
		GpioModeAltFn1,
		GpioModeAltFn2,
		GpioModeAltFn3,
		GpioModeAltFn4,
		GpioModeAltFn5,
		GpioModeEnumerationEnd
	};

	class GpioPin {
		pvper::hw::GpioMode _mode;
		uint32_t _pin;
		bool _state;

	public:
		GpioPin() __attribute__((deprecated));
		
		static const GpioPin&
		immutablePin(const uint16_t pin);

		static void
		initialize();

		static GpioPin&
		pin(const uint16_t pin);

		void
		invert();
		
		const bool
		read() const;
		
		void
		setMode(const GpioMode mode);
		
		void
		write(const bool state);
	};

}
}