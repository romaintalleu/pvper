#pragma once
#include <priv/base.h>

namespace pvper {
namespace hw {

	class Serial {
	public:
		enum Color {
			Reset = 0,
			Bold = 1,
			ForeBlack = 30,
			ForeRed = 31,
			ForeGreen = 32,
			ForeYellow = 33,
			ForeBlue = 34,
			ForeMagenta = 35,
			ForeCyan = 36,
			ForeWhite = 37,
			BackBlack = 40,
			BackRed = 41,
			BackGreen = 42,
			BackYellow = 43,
			BackBlue = 44,
			BackMagenta = 45,
			BackCyan = 46,
			BackWhite = 47,
		};

		static Serial& shared(void);

		uint8_t
		getc(void);

		void
		putc(uint8_t byte);

		void
		puts(const char* str);

		void
		setColor(const Color& color);

		void
		write(const void *buffer, const size_t size);

		Serial&
		operator<<(const Color& color);

		Serial&
		operator<<(const bool& value);

		Serial&
		operator<<(const uint32_t& value);

		Serial&
		operator<<(const size_t& value) { return operator<<((uint32_t)value); }

		Serial&
		operator<<(const void* addr);

		Serial&
		operator<<(const char& ch);

		Serial&
		operator<<(const char* str);

	private:
		Serial();
	};

}
}