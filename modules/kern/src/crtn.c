typedef void (*fptr)(void);

fptr _init_array_end[0] __attribute__ ((used, section(".init_array"), aligned(sizeof(fptr)))) = { };
fptr _fini_array_end[0] __attribute__ ((used, section(".fini_array"), aligned(sizeof(fptr)))) = { };