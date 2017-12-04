#ifndef IO_H_
#define IO_H_

#include <k/types.h>
#include "../libs/libc/include/stdio.h"

void init_com();

static inline void outb(u16 port, u8 val);
static inline u8 inb(u16 port);

static inline void outb(u16 port, u8 val)
{
	/*
	*** Avoid unused error
	***(void)port;
	***(void)val;
	*/
	asm volatile("outb %0, %1\n\t"
								:/* No output */
								:"a" (val), "d" (port));

}

static inline u8 inb(u16 port)
{
	/*
	***Avoid unused error
	***(void)port;
	*/
  u8 res = 0;
	asm volatile("inb %1, %0\n\t"
							: "=&a" (res)
							: "d" (port));
	return res;
}

#endif				/* !IO_H_ */
