#include "gdt.h"

void init_gdt_desc(u32 base, u32 limite, u8 acces, u8 other, gdtdesc *desc)
{
    desc->limit = (limite & 0xffff);
    desc->base = (base & 0xffff);
    desc->base_low = (base & 0xff0000) >> 16;
    desc->access = acces;
    desc->segment_limit = (limite & 0xf0000) >> 16;
    desc->other = (other & 0xf);
    desc->base_high = (base & 0xff000000) >> 24;
    return;
}

void load_gdt()
{
  /* initialize gdt segments */
    init_gdt_desc(0x0, 0x0, 0x0, 0x0, &entry[0]); /* Null Segment */
    init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, &entry[1]);    /* code */
    init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, &entry[2]);    /* data */

    /*initialize the gdtr structure */
    ptr.base = &entry; /* gdt base address */
    ptr.limit = sizeof(entry) - 1; /* gdt size - 1 */

   /* load the gdtr registry */
    asm("lgdtl (ptr)");

   /* initiliaz the segments */
    asm("movw $0x10, %ax    \n \
         movw %ax, %ds    \n \
         movw %ax, %es    \n \
         movw %ax, %fs    \n \
         movw %ax, %gs    \n \
         ljmp $0x08, $next    \n \
         next:        \n"); 
}
