#include <lpc214x.h>

void pll()
{
  PLL0CON=0X01;
  PLL0CFG=0X24;
  PLL0FEED=0XAA;
  PLL0FEED=0X55;
  while((PLL0STAT&(1<<10))!=0);
  PLL0CON=0X03;
  PLL0FEED=0XAA;
  PLL0FEED=0X55;
  VPBDIV=0x01;             //pclk=60mhz
}
void ser_int(void)
{
  PINSEL0=0X5;
  U0LCR=0X83;            //8-data bits, 1 Stop bit, Disable Parity and Enable DLAB
  U0DLL=135;
  U0DLM=1;
  U0LCR=0X03;            //cleared DLAB
}

void TxChar(char ch) /*A function to send a byte on UART0 */
{
	U0THR = ch;
	while((U0LSR&0x40)==0);	/* Wait till THRE bit becomes 1 which tells that transmission is completed */
}

int rx()
{
  unsigned char a;
  while((U0LSR&(1<<0))==0);         //Checking RDR bit
  a=U0RBR;
  return a;
}

void delay_ms(unsigned int ms)
{
    T0CTCR=0x0;                                 
    T0TCR=0x00;                
    T0PR=59999;                 
    T0TCR=0x01;                
    while(T0TC<ms);           
    T0TCR=0x00;                 
    T0TC=0;   
}

int rx_num(){
	int num=0,i=0;
	char c;
	c=rx();
	while(c!=13 && i<3)
	{
		if(c>=48 && c<=57)
			{
				num=num*10+(c-48);
		  }
		else return 0;
		c=rx();
		i++;
	}
	return num;
}
void DisplayString(char *s)
{	
	while(*s!='\0'){
		TxChar(*s++);
	}
}

void isArmstrong(int num)
{
	int sum=0,rem,originalNum=num;
	while(num!=0){
		rem=num%10;
		sum+=rem*rem*rem;
		num/=10;
	}if(sum==originalNum){
		DisplayString("Armstrong");
		DisplayString("\r\n");
	}else{
		DisplayString("Not Armstrong");
		DisplayString("\r\n");
	}
}