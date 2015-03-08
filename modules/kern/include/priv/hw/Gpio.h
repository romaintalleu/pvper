#pragma once
#include <priv/base.h>

#define GPIO_PIN_COUNT 54

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

	protected:
		GpioPin();

		static uint32_t s_nextPin;
		static GpioPin s_pins[GPIO_PIN_COUNT];
	};

}
}