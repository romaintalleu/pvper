#include <priv/hw/CPU.h>
#include <priv/hw/MMIO.h>
#include <priv/hw/Serial.h>

size_t strlen(const char* str) {
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}

/*static*/ pvper::hw::Serial&
pvper::hw::Serial::shared()
{
	static pvper::hw::Serial instance;
	return instance;
}

pvper::hw::Serial::Serial() {
	pvper::hw::MMIO::write(ARM_UART0_CR, 0);
	pvper::hw::MMIO::write(ARM_GPIO_PUD, 0);
	pvper::hw::CPU::delay(150);
	pvper::hw::MMIO::write(ARM_GPIO_PUDCLK0, (1<<14) | (1<<15));
	pvper::hw::CPU::delay(150);
	pvper::hw::MMIO::write(ARM_GPIO_PUDCLK0, 0);
	pvper::hw::MMIO::write(ARM_UART0_ICR, 0x7FF);
	pvper::hw::MMIO::write(ARM_UART0_IBRD, 1);
	pvper::hw::MMIO::write(ARM_UART0_FBRD, 40);
	pvper::hw::MMIO::write(ARM_UART0_LCRH, (1<<4) | (1<<5) | (1<<6));
	pvper::hw::MMIO::write(ARM_UART0_IMSC, (1<<1) | (1<<4) | (1<<5) | (1<<6) | (1<<7) | (1<<8) | (1<<9) | (1<<10));
	pvper::hw::MMIO::write(ARM_UART0_CR, (1<<0) | (1<<8) | (1<<9));
}

uint8_t
pvper::hw::Serial::getc(void)
{
	while( pvper::hw::MMIO::read(ARM_UART0_FR) & (1 << 4) ) { }
	return pvper::hw::MMIO::read(ARM_UART0_DR);
}

void
pvper::hw::Serial::putc(uint8_t byte)
{
	while( pvper::hw::MMIO::read(ARM_UART0_FR) & (1 << 5) ) { }
	return pvper::hw::MMIO::write(ARM_UART0_DR, byte);
}

void
pvper::hw::Serial::puts(const char* str)
{
	write( (const unsigned char *)str, strlen(str) );
}

void
pvper::hw::Serial::setColor(const pvper::hw::Serial::Color& color)
{
	puts("\e[");
	puts(todec(color, 0));
	putc('m');
}

void
pvper::hw::Serial::write(const void *buffer, const size_t size)
{
	const uint8_t *byteBuffer = (uint8_t *)buffer;
	for (size_t i(0); i < size; i++)
		putc(byteBuffer[i]);
}

pvper::hw::Serial&
pvper::hw::Serial::operator<<(const pvper::hw::Serial::Color& color)
{
	setColor(color);
	return *this;
}

pvper::hw::Serial&
pvper::hw::Serial::operator<<(const bool& value)
{
	puts(value ? "true" : "false");
	return *this;
}

pvper::hw::Serial&
pvper::hw::Serial::operator<<(const uint32_t& value)
{
	puts(todec(value, 0));
	return *this;
}

pvper::hw::Serial&
pvper::hw::Serial::operator<<(const void* addr)
{
	puts("0x");
	puts(tohex((size_t)addr, 4));
	return *this;
}

pvper::hw::Serial&
pvper::hw::Serial::operator<<(const char& ch)
{
	putc(ch);
	return *this;
}

pvper::hw::Serial&
pvper::hw::Serial::operator<<(const char* str)
{
	puts(str);
	return *this;
}