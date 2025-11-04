#include <asf.h>

#define LCD_RS     PIN_PA19
#define LCD_EN     PIN_PA18
#define LCD_D4     PIN_PA21
#define LCD_D5     PIN_PA20
#define LCD_D6     PIN_PB17
#define LCD_D7     PIN_PB16


void lcd_send_nibble(unsigned char nibble);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_init(void);
void lcd_str(const char *str);
void lcd_int(int num);


void lcd_send_nibble(unsigned char nibble)
{
	port_pin_set_output_level(LCD_D4, (nibble >> 0) & 1);
	port_pin_set_output_level(LCD_D5, (nibble >> 1) & 1);
	port_pin_set_output_level(LCD_D6, (nibble >> 2) & 1);
	port_pin_set_output_level(LCD_D7, (nibble >> 3) & 1);
}

void lcd_cmd(unsigned char cmd)
{
	PORT->Group[LCD_RS >> 5].OUTCLR.reg = (1 << (LCD_RS & 0x1F));
	
	lcd_send_nibble(cmd >> 4);
	PORT->Group[LCD_EN >> 5].OUTSET.reg = (1 << (LCD_EN & 0x1F));
	delay_ms(2);
	PORT->Group[LCD_EN >> 5].OUTCLR.reg = (1 << (LCD_EN & 0x1F));
	
	lcd_send_nibble(cmd & 0x0F);
	PORT->Group[LCD_EN >> 5].OUTSET.reg = (1 << (LCD_EN & 0x1F));
	delay_ms(2);
	PORT->Group[LCD_EN >> 5].OUTCLR.reg = (1 << (LCD_EN & 0x1F));
	
}

void lcd_data(unsigned char d)
{
	PORT->Group[LCD_RS >> 5].OUTSET.reg = (1 << (LCD_RS & 0x1F));
	
	lcd_send_nibble(d >> 4);
	PORT->Group[LCD_EN >> 5].OUTSET.reg = (1 << (LCD_EN & 0x1F));
	delay_ms(2);
	PORT->Group[LCD_EN >> 5].OUTCLR.reg = (1 << (LCD_EN & 0x1F));
	
	lcd_send_nibble(d & 0x0F);
	PORT->Group[LCD_EN >> 5].OUTSET.reg = (1 << (LCD_EN & 0x1F));
	delay_ms(2);
	PORT->Group[LCD_EN >> 5].OUTCLR.reg = (1 << (LCD_EN & 0x1F));
}

void lcd_init(void)
{
	
    PORT->Group[0].DIRSET.reg = (1 << 19) | (1 << 18) | (1 << 21) | (1 << 20);
    PORT->Group[1].DIRSET.reg = (1 << 17) | (1 << 16);	
	delay_ms(20);
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0c);
	lcd_cmd(0x28);
	lcd_cmd(0x80);
}

void lcd_str(const char *str)
{
	while (*str)
	{
		lcd_data(*str++);
	}
}

void lcd_int(int num)
{
	char buffer[10];
	sprintf(buffer, "%d", num);
	lcd_str(buffer);
}

