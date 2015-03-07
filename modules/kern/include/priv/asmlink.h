#pragma once
#include <priv/base.h>

EXTERNC void __halt(void) __attribute__((naked, noreturn));
#define __nop() __asm__ volatile("nop")