ENTRY(_start)

SECTIONS
{
	/* Starts at LOADER_ADDR. */
	. = 0x8000;
	__start = .;

	__text_start = .;
	.text :
	{
		KEEP(*(.text.boot))
		*(.text)
		*(.text.*)
	}
	__text_end = .;

	/* Include the list of initialization functions sorted. */
	.init_array :
	{
		__init_array_start = .;
		KEEP (*(.init_array*))
		__init_array_end = .;
	}

	/* Include the list of deinitialization functions sorted. */
	.fini_array :
	{
		__fini_array_start = .;
		KEEP (*(.fini_array*))
		__fini_array_end = .;
	}
	. = ALIGN(4096);

	__rodata_start = .;
	.rodata :
	{
		KEEP(*(.rodata*));
	}
	. = ALIGN(4096); /* align to page size */
	__rodata_end = .;

	__data_start = .;
	.data :
	{
		KEEP(*(.data*));
	}
	. = ALIGN(4096); /* align to page size */
	__data_end = .;

	__bss_start = .;
	.bss :
	{
		KEEP(*(.bss*));
	}
	. = ALIGN(4096); /* align to page size */
	__bss_end = .;

	__end = .;
}