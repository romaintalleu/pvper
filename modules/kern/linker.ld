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
	}
	. = ALIGN(4096); /* align to page size */
	__text_end = .;

	/* Include the list of initialization functions sorted. */
	.init_array :
	{
		crti.o(.init_array)
		KEEP (*(SORT(EXCLUDE_FILE(crti.o crtn.o) .init_array.*)))
		KEEP (*(EXCLUDE_FILE(crti.o crtn.o) .init_array))
		crtn.o(.init_array)
	}

	/* Include the list of termination functions sorted. */
	.fini_array :
	{
		crti.o(.fini_array)
		KEEP (*(SORT(EXCLUDE_FILE(crti.o crtn.o) .fini_array.*)))
		KEEP (*(EXCLUDE_FILE(crti.o crtn.o) .fini_array))
		crtn.o(.fini_array)
	}

	__rodata_start = .;
	.rodata :
	{
		*(.rodata)
	}
	. = ALIGN(4096); /* align to page size */
	__rodata_end = .;

	__data_start = .;
	.data :
	{
		*(.data)
	}
	. = ALIGN(4096); /* align to page size */
	__data_end = .;

	__bss_start = .;
	.bss :
	{
		*(.bss)
	}
	. = ALIGN(4096); /* align to page size */
	__bss_end = .;
	__end = .;

	__exidx_start = .;
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	}
	__exidx_end = .;
}