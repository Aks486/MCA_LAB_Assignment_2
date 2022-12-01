#include "header.h"

int main(void)
{
	pll();
	ser_int();
	int num=0;
	while(1)
	{
		num=rx_num();
		if(num==0)
		{
			continue;
		}else{
				isArmstrong(num);
			}
	}
	return 0;
}
