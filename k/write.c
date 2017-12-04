#include "io.h"

/* Port Communication adress Values */
#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8
/* Value offset registers */
#define IER_Offset 0x01 // Interrupt Enable Register
#define THR_Offset 0x01 // Transmitter Holding Register
#define IIR_Offset 0x02 // Interrupt Identification Register
#define LCR_Offset 0x03 // Line Control Register
/* Value set to have different behavior of registers */
#define Latch_Low 0x03 // Value of Latch low byte to set brs at 38400
#define Latch_High 0x00 // Value of Latch high byte to set brs at 38400

void init_com()
{
	u8 res = 0;
	u8 value = 0;
	/***** COM1 + 1 Enable Transmitter Holding Register Empty Interrup bit1 *****/
	outb(COM1 + IER_Offset, 0x01);

	/***** COM1 + 2 : (FIFO) bit0 | (Interrupt Trigger level 14 bytes) bit6&7
	| (Clear transmit FIFO)  bit2| (Clear receive FIFO) bit1 *****/
	res = inb(COM1 + IIR_Offset);
	value = res | 0xC7;
	outb(COM1 + IIR_Offset, value);

	/***** COM1 + 3 (8 bits length) bit 1&2 | (No parity) bit 3 *****/
	outb(COM1 + LCR_Offset, 0x03);

	/***** Baud Rates value set to 38400 *****/
	//Read LCR puis ou dessus avec 0x80 puis out dessus
	res = inb(COM1 + LCR_Offset);
	value = res | 0x80;
	outb(COM1 + LCR_Offset, value); // Enable DLAB (Set the 7th bit of LCR register)

	res = inb(COM1);
	value = res | Latch_Low;
	outb(COM1, value)	; // Set Latch_Low at 3

	res = inb(COM1);
	value = res | Latch_High;
	outb(COM1 + IER_Offset, value); // Set Latch_High at 0

	res = inb(COM1 + LCR_Offset);
	value = res & ~0x80;
	outb(COM1 + LCR_Offset, value);
}

int write (const char* buf, size_t count)
{
  for (size_t i = 0; i < count; i++)
    outb(COM1, buf[i]);

  return 0;
}
