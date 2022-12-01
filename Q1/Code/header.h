#include <lpc214x.h>
#define bit(x) (1<<x);

void pll_init(void);
void lcd_int(void);
void lcd_cmd(unsigned char );
void lcd_data(unsigned char );
void delay_ms(unsigned int );
void DisplayString(char* );
int isPalindrome(char* );
void ser_int(void);
int rx(void);

void pll_init(void){
    PLL0CON=0x01;
    PLL0CFG=0x24;
    PLL0FEED=0xaa;
    PLL0FEED=0x55;
    while(!(PLL0STAT&(1<<10)));
    PLL0CON=0x03;
    PLL0FEED=0xaa;
    PLL0FEED=0x55;
    VPBDIV=0x01;
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
    delay_ms(2);
    IO1CLR|=bit(27);               
}

void lcd_data(unsigned char b){
    IO1PIN&=0x00;
    IO1PIN=(b<<16);
    IO1SET|=bit(25);               
    IO1CLR|=bit(26);               
    IO1SET|=bit(27);              
    delay_ms(2);
    IO1CLR|=bit(27);               
}
void delay_ms(unsigned int ms){
    T0CTCR=0x0;                                 
    T0TCR=0x00;                
    T0PR=59999;                 
    T0TCR=0x01;                
    while(T0TC<ms);           
    T0TCR=0x00;                 
    T0TC=0;   
}

void ser_int(void)
{
  PINSEL0=0X5;
  U0LCR=0X83;            //8-data bits, 1 Stop bit, Disable Parity and Enable DLAB
  U0DLL=135;
  U0DLM=1;
  U0LCR=0X03;            //cleared DLAB
}
int rx()
{
  unsigned char a;
  while((U0LSR&(1<<0))==0);         //Checking RDR bit
  a=U0RBR;
  return a;
}

int isPalindrome(char* string)
{
    char *ptr,*rev;
    ptr=string;
    while(*ptr!='\0') {
        ++ptr;
    }
    --ptr;
    for (rev=string;ptr>=rev;) {
        if (*ptr==*rev) {
            --ptr;
            rev++;
        }
        else
            break;
    }
    if (rev>ptr)
       return 1;
    else
        return 0;
}
 
void DisplayString(char* s){ 
	while(*s!='\0'){ 
		lcd_data(*s++);
	}
}

char* rec_string()
{		char string[16]; 
	  char c;
		int i=0; //Count that holds number of characters recieved
		c=rx(); //Recieve one character
		while(c!=13 && i<14){  //13 is ASCII value for "Enter",whenever enter is encountered loop stops  
				string[i++]=c;  
				c=rx();
			}
	  string[i]='\0';
		return string;//Make ith element the end of string
}
