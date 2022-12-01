#include <lpc214x.h>
#include <stdint.h>
#include <stdio.h>
#define bit(x) (1<<x);

void pll_init(void);
void lcd_int(void);
void lcd_cmd(unsigned char );
void lcd_data(unsigned char );
void delay_ms(void);
void DisplayString(char* );
int ADC_init(void);

void delay_ms()
{
	for(int i=0;i<5000;i++);
}
//Initializing LCD
void lcd_int(void){
    lcd_cmd(0x38);
    lcd_cmd(0x0c);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
    lcd_cmd(0x80);
}

void lcd_cmd(unsigned char a){
    IO1PIN&=0x00;
    IO1PIN=(a<<16);
    IO1CLR|=bit(25);  //RS             
    IO1CLR|=bit(26);   //RW         
    IO1SET|=bit(27);       //E        
    delay_ms();
    IO1CLR|=bit(27);               
}

void lcd_data(unsigned char b){
    IO1PIN&=0x00;
    IO1PIN=(b<<16);
    IO1SET|=bit(25);               
    IO1CLR|=bit(26);               
    IO1SET|=bit(27);              
    delay_ms();
    IO1CLR|=bit(27);               
}


int ADC_init(void)
{
	int result=0;
		AD0CR=0x00200402;
		AD0CR=AD0CR|(1<<24);
		while(!(AD0GDR&0x80000000));
		AD0CR&=~0X01000000;
		result=AD0GDR;
		result=(result>>6);
		result=(result&0x000003FF);
		result = ((result*100*3.3)/1023);
		return result;
}

void DisplayString(char *s)
{	
	while(*s!='\0'){
		lcd_data(*s++);
	}
}

void printVoltage(int o)
{ int i,outdec;
	char volt[20];
	i=o/100;
		outdec=o-i*100;
	sprintf(volt,"%d.%d V",i,outdec);
		DisplayString(volt);
}