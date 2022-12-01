#include "header.h"

int main(void)
{
	IO1DIR|=0XFFFFFFFF;
	lcd_int();
	PINSEL1 = 0x01000000;
	int voltage,out,outdec,i;
	char volt[18];
	DisplayString("VOLTAGE: ");
	while(1)
	{	 voltage=ADC_init();
		lcd_cmd(0x80);
		lcd_cmd(0xC0);
		printVoltage(voltage);
		delay_ms();
	}
	return 0;
}