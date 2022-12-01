#include"header.h"

int main()
{ 
	int deg=0,sine;
  float r;
  for(int i=0;i<steps;i++)
    { 
			r=deg*3.14/180;
      sine=512+512*sin(r);
      printf("%d,",sine);
      deg+=180/steps;
    } 
    deg=0;
  for(int i=0;i<steps;i++)
    { 
			r=deg*3.14/180;
      sine=512-512*sin(r);
      printf("%d,",sine);
      deg+=180/steps;
    }
	return 0;	
}		