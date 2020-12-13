int kontrol;
#include "stm32f10x.h"
void SysTick_Handler(void){
	if (kontrol==1){
		kontrol =0;
		GPIOC -> BSRR |= (1<<13);
	}
	else{
		kontrol = 1;
		GPIOC -> BSRR |=(1<<(13+16));
	}
		
	}
int main(){
	RCC -> APB2ENR |= (1<<4);
	GPIOC -> CRH |=  (1<<20)|(1<<21);
	GPIOC -> CRH &=~ (1<<22)|(1<<23);
	SysTick -> LOAD =RCC_CFGR_MCO_SYSCLK/8; 													//72Mhz/8 = 9.000.000 == 100010010101010001000000 bu degeri load registerina yüklüyoruz asagi saymaya baslicak 0 oldugunda 1sn geçmis olcak
	SysTick->CTRL=SysTick_CTRL_ENABLE_Msk|SysTick_CTRL_TICKINT_Msk;  //SysTick_CTRL_ENABLE_Msk = 1UL(0..001) | SysTick_CTRL_TICKINT_Msk = 1UL(0.001)  unsigned long
	while(1){
	/* program sonsuz döngüye girrmis oldu.
		ama sayaç 0 oldgunda Systick interupt olusturcak ve SysTick_Handler fonksiyonunu çalistircak.
	*/
	}
}
