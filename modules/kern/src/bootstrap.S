	.section ".text.boot"
	.globl _start
	_start:
mov sp, #0x8000

ldr r3, =bootstrap
blx r3

	.globl __halt
	__halt:
wfe
b __halt