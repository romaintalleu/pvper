#include <priv/hw/CPU.h>
#include <priv/hw/Gpio.h>
#include <priv/hw/Memory.h>
#include <priv/hw/Serial.h>
#include <priv/hw/Timer.h>
#include <priv/base.h>

#include <angle/list.hxx>

using namespace pvper::hw;

void printLinkedListOfUInt32(const angle::List<uint32_t>& linkedList)
{
	Serial& line = pvper::hw::Serial::shared();
	line << "linkedList";
	auto it = linkedList.constIterator();
	while (it == true)
	{
		line << " > " << *it;
		++it;
	}
	line << "\n";
}

EXTERNC void kinit(const uint32_t r0, const uint32_t machCode, const uint32_t atags) {
	assert(r0 == 0);

	Serial& line = pvper::hw::Serial::shared();
	line << "Ok" << '\n';

	line << (machCode == 0x00000C42 ? "Raspberry Pi detected, everything should be OK for model B.\n" : "Unknown platform, good luck to you!\n");
	
	// GpioPin led = GpioPin::pin(17);
	// led.setMode(GpioMode::GpioModeOutput);
	// led.write(true);
	while (true) {
		uint32_t i = 2;
		while (i <= 11) {
			GpioPin led = GpioPin::pin(i);
			led.setMode(GpioMode::GpioModeOutput);
			led.write(true);
			Timer::sleep(100000);
			led.write(false);
			i += 1;
		}
	}
}
