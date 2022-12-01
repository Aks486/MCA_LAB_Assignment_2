#include "header.h"

int main(void)
{
	IO1DIR|=0xFFFFFFFF;
	pll_init();
	ser_int();
	lcd_int();
	char *s;
	while(1)
	{	
		s = rec_string();
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		DisplayString(s);
		lcd_cmd(0xC0);
		if(isPalindrome(s))
		{
			DisplayString("It is palindrome");
		}else
			DisplayString("It is not palindrome");
	}
	return 0;
}