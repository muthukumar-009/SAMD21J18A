#include <asf.h>
#include "lcd_header.h"

#define SW1  PIN_PA12

int main(void)
{
	unsigned int count = 0;

	system_init();
	delay_init();
	lcd_init();

	// Configure SW1 (PA12)
	PORT->Group[0].DIRCLR.reg = (1 << 12);
	PORT->Group[0].PINCFG[12].bit.INEN = 1;
	PORT->Group[0].PINCFG[12].bit.PULLEN = 1;
	PORT->Group[0].OUTSET.reg = (1 << 12); // Enable pull-up

	// Initial Display
	lcd_cmd(0x80);
	lcd_str("*COIMBATORE*");
	lcd_cmd(0xC0);
	lcd_str("***AUTOMATION***");
	delay_s(2);
	lcd_cmd(0x01);

	while (1)
	{
		if (((PORT->Group[0].IN.reg >> 12) & 1) == 0)
		{
			count++;
			lcd_cmd(0x80);
			lcd_str("COUNT:-");
			lcd_cmd(0xC0);
			lcd_int(count);

			while (((PORT->Group[0].IN.reg >> 12) & 1) == 0); // Wait for release
			delay_ms(200); // Debounce
		}
	}
}
