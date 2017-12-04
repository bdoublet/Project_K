#ifndef GDT_H

#include <k/types.h>

typedef struct {
  unsigned short limit;
  unsigned short base;
  unsigned char base_low;
  unsigned char access;
  unsigned char segment_limit : 4;
  unsigned char other : 4;
  unsigned char base_high;
}__attribute__ ((packed)) gdtdesc;

typedef struct {
  unsigned short limit;
  unsigned int base;
}__attribute__ ((packed)) gdt_r;

gdtdesc entry[3];
gdt_r ptr;
void init_gdt_desc(u32 base, u32 limite, u8 acces, u8 other, gdtdesc *desc);
void load_gdt();

#endif /* GDT_H */
