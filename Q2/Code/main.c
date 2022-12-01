#include "header.h"

int main(void){
	pll_init();
	IO0DIR=0X4;
	while(1)
	{
		if((IO0PIN&&(1<<0))==0)
		{
			IO0SET|=bit(2);
			delay_ms(1000);
			IO0CLR|=bit(2);
			delay_ms(1000);
		}else
		{
			IO0SET|=bit(2);
			delay_ms(500);
			IO0CLR|=bit(2);
			delay_ms(500);
		}
	}
	return 0;
}