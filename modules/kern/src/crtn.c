typedef void (*fptr)(void);

fptr __init_array_end[0] __attribute__ ((used, section(".init_array"), aligned(sizeof(fptr)))) = { };
fptr __fini_array_end[0] __attribute__ ((used, section(".fini_array"), aligned(sizeof(fptr)))) = { };