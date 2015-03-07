#pragma once
#include <priv/base.h>

namespace pvper {
namespace hw {

	class Serial {
	public:
		static Serial& shared(void);

		virtual uint8_t
		getc(void) = 0;

		virtual void
		putc(uint8_t byte) = 0;

		virtual void
		puts(const char* str) = 0;

		virtual void
		write(const void *buffer, const size_t size) = 0;
	};

}
}