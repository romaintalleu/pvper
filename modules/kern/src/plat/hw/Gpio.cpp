#include <priv/hw/CPU.h>
#include <priv/hw/Gpio.h>
#include <priv/hw/MMIO.h>
#include <priv/hw/Sync.h>

#define GPIO_PIN_COUNT 54

namespace pvper {
namespace hw {
	static uint32_t s_nextPin;

#pragma GCC diagnostic push // disable deprecation for usage of GpioPin ctor
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
	static GpioPin s_pins[GPIO_PIN_COUNT];
#pragma GCC diagnostic pop

	/*static*/ const GpioPin&
	GpioPin::immutablePin(const uint16_t pin)
	{
		assert(pin < GPIO_PIN_COUNT);
		return s_pins[pin];
	}

	/*static*/ void
	GpioPin::initialize()
	{
		s_nextPin = 0;
		for (uint32_t _(0); _<GPIO_PIN_COUNT; _++)
		{
#pragma GCC diagnostic push // disable deprecation for usage of GpioPin ctor
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
			s_pins[_] = GpioPin();
#pragma GCC diagnostic pop
		}
	}

	/*static*/ GpioPin&
	GpioPin::pin(const uint16_t pin)
	{
		assert(pin < GPIO_PIN_COUNT);
		return s_pins[pin];
	}
	
	GpioPin::GpioPin() :
	_mode(pvper::hw::GpioMode::GpioModeUnknown),
	_pin(s_nextPin++)
	{ }
	
	void
	GpioPin::invert()
	{
		assert(_mode == pvper::hw::GpioModeOutput);
		write(!_state);
	}
		
	const bool
	GpioPin::read() const
	{
		assert( _pin < GPIO_PIN_COUNT && (_mode == pvper::hw::GpioModeInput || _mode == pvper::hw::GpioModeInputPullDown || _mode == pvper::hw::GpioModeInputPullUp) );
	
		pvper::barrier::data::mem();
	
		uint32_t levelRegister = ARM_GPIO_LEV0 + (_pin / 32) * 4;
		uint32_t shift = _pin % 32;
	
		uint32_t result = pvper::hw::MMIO::read(levelRegister) & (1 << shift) ? true : false;
	
		pvper::barrier::data::mem();
	
		return result;
	}
		
	void
	GpioPin::setMode(const pvper::hw::GpioMode mode)
	{
		assert(mode < pvper::hw::GpioModeEnumerationEnd && mode != pvper::hw::GpioModeUnknown);
		assert(_pin < GPIO_PIN_COUNT);
		_mode = mode;
	
		pvper::barrier::data::mem();
	
		static const uint32_t funcMap[11] = {0, 0,1,0,0, 4,5,6,7,3,2};
	
		uint32_t reg = ARM_GPIO_FSEL0 + ((_pin / 10) * 4);
		uint32_t shift = (_pin % 10) * 3;
		uint32_t regValue = pvper::hw::MMIO::read(reg);
		regValue &= ~(7 << shift);
		regValue |= funcMap[mode] << shift;
		pvper::hw::MMIO::write(reg, regValue);
	
		switch (mode)
		{
		case pvper::hw::GpioModeOutput:
			write(false);
		case pvper::hw::GpioModeInput:
		{
			uint32_t clockReg = ARM_GPIO_PUDCLK0 + ((_pin / 32) * 4);
			uint32_t shift = _pin % 32;
	
			pvper::hw::MMIO::write(ARM_GPIO_PUD, mode);
			pvper::hw::CPU::delay(150);
			pvper::hw::MMIO::write(clockReg, 0 << shift);
			pvper::hw::CPU::delay(150);
			pvper::hw::MMIO::write(ARM_GPIO_PUD, 0);
			pvper::hw::MMIO::write(clockReg, 0);
			break;
		}
		case pvper::hw::GpioModeInputPullUp:
		{
			uint32_t clockReg = ARM_GPIO_PUDCLK0 + ((_pin / 32) * 4);
			uint32_t shift = _pin % 32;
	
			pvper::hw::MMIO::write(ARM_GPIO_PUD, 2);
			pvper::hw::CPU::delay(150);
			pvper::hw::MMIO::write(clockReg, 1 << shift);
			pvper::hw::CPU::delay(150);
			pvper::hw::MMIO::write(ARM_GPIO_PUD, 0);
			pvper::hw::MMIO::write(clockReg, 0);
			break;
		}
		case pvper::hw::GpioModeInputPullDown:
		{
			uint32_t clockReg = ARM_GPIO_PUDCLK0 + ((_pin / 32) * 4);
			uint32_t shift = _pin % 32;
	
			pvper::hw::MMIO::write(ARM_GPIO_PUD, 1);
			pvper::hw::CPU::delay(150);
			pvper::hw::MMIO::write(clockReg, 1 << shift);
			pvper::hw::CPU::delay(150);
			pvper::hw::MMIO::write(ARM_GPIO_PUD, 0);
			pvper::hw::MMIO::write(clockReg, 0);
			break;
		}
		default:
			break;
		}
	}
		
	void
	GpioPin::write(const bool state)
	{
		assert(_mode == pvper::hw::GpioModeOutput && _pin < GPIO_PIN_COUNT);
	
		pvper::barrier::data::mem();
		_state = state;
	
		uint32_t reg = (_state ? ARM_GPIO_SET0 : ARM_GPIO_CLR0) + (_pin / 32) * 4;
		uint32_t shift = _pin % 32;
		pvper::hw::MMIO::write(reg, 1 << shift);
	
		pvper::barrier::data::mem();
	}
}
}