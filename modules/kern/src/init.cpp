#include <priv/hw/CPU.h>
#include <priv/hw/Gpio.h>
#include <priv/hw/Serial.h>
#include <priv/base.h>

EXTERNC void kinit(const uint32_t r0, const uint32_t machCode, const uint32_t atags) {
	assert(r0 == 0);

	pvper::hw::Serial& line = pvper::hw::Serial::shared();
	pvper::hw::GpioPin& actLed = pvper::hw::GpioPin::pin(16);
	actLed.setMode(pvper::hw::GpioModeOutput);

	line.puts("Model: 0x");
	line.puts(tohex(machCode, 4));
	line.puts("\r\n");

	line.puts("Echo server v0.1 — Start typing something and get it back!\r\n");

	while (true) {
		actLed.invert();
		line.putc(line.getc());
		actLed.invert();
		pvper::hw::CPU::delay(250000);
	}
	__halt();
}