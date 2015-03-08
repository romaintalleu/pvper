#include <priv/hw/CPU.h>
#include <priv/hw/Gpio.h>
#include <priv/hw/Memory.h>
#include <priv/hw/Serial.h>
#include <priv/base.h>

using namespace pvper::hw;

EXTERNC void kinit(const uint32_t r0, const uint32_t machCode, const uint32_t atags) {
	assert(r0 == 0);

	Serial& line = pvper::hw::Serial::shared();

	line.puts("Model: 0x");
	line.puts(tohex(machCode, 4));
	line.puts("\r\n");

	int *array = new int[10];
	line.puts("array @ 0x");
	line.puts(tohex((uint32_t)array,4));
	line.puts("\r\n");
	for (uint32_t i(0); i < 10; i++)
	{
		line.puts("\tarray[");
		line.puts(todec(i,0));
		line.puts("] = ");
		line.puts(todec(array[i],0));
		line.puts("\r\n");
	}
	for (uint32_t i(0); i < 10; i++)
	{
		array[i] = 10-i;
	}
	for (uint32_t i(0); i < 10; i++)
	{
		line.puts("\tarray[");
		line.puts(todec(i,0));
		line.puts("] = ");
		line.puts(todec(array[i],0));
		line.puts("\r\n");
	}
	delete array;
	
	__halt();
}