typedef void (*fptr)(void);

extern fptr _init_array_start[0], _init_array_end[0];
extern fptr _fini_array_start[0], _fini_array_end[0];

void _fini(void)
{
	for (fptr* f = _fini_array_start; f != _fini_array_end; f++)
		(*f)();
}

void _init(void)
{
	for (fptr* f = _init_array_start; f != _init_array_end; f++)
		(*f)();
}

fptr _init_array_start[0] __attribute__ ((used, section(".init_array"), aligned(sizeof(fptr)))) = { };
fptr _fini_array_start[0] __attribute__ ((used, section(".fini_array"), aligned(sizeof(fptr)))) = { };