typedef void (*fptr)(void);

extern fptr __init_array_start[0], __init_array_end[0];
extern fptr __fini_array_start[0], __fini_array_end[0];

void _fini(void)
{
	for (fptr* f = __fini_array_start; f != __fini_array_end; f++)
		(*f)();
}

void _init(void)
{
	for (fptr* f = __init_array_start; f != __init_array_end; f++)
		(*f)();
}

fptr __init_array_start[0] __attribute__ ((used, section(".init_array"), aligned(sizeof(fptr)))) = { };
fptr __fini_array_start[0] __attribute__ ((used, section(".fini_array"), aligned(sizeof(fptr)))) = { };