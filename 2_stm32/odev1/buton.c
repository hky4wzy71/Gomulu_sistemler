
#include "stm32f10x.h"

int main(void){		
	RCC->APB2ENR |=(1<<4);							//c port aktf														(port c )
	GPIOC->CRH|=((1<<21)|(1<<20));			//11: Output mode, max speed 50 MHz.    (port 13)
	GPIOC->CRH&=~((1<<23)|(1<<22)); 		//00: General purpose output push-pull  (port 13)
	
	
	GPIOC->CRH &=~((1<<25)|(1<<24)); 		//00: Input mode (reset state)		      (port 14)
	GPIOC->CRH |=(1<<27); 							//10: Input with pull-up / pull-down    (port 14)
	GPIOC->CRH &=~(1<<26);							//   			 			  						 			    (port 14)

	
	
	
	while(1){
		if(GPIOC -> IDR & (1<<14))				//GPIOC-> x & 1                         x = basilmadiginda 1,basildiginda 0
			  GPIOC -> ODR |=(1<<13);      	//buton basilmadi. 13.pini 0 (led off)
		
		else{ 														// butona basildi. 13.pini 1 (led on)
			for(int count=0; count<5; count++){				
			GPIOC -> ODR |=(1<<13);
			for(int i=0; i<2000000;i++);
			GPIOC -> ODR &=~(1<<13);
			for(int i=0; i<2000000;i++);
			}			
		}
	}
}