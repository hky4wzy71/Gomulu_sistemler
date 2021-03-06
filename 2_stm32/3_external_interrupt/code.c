#include "stm32f10x.h"
void EXTI3_IRQHandler(void){ //interrupt fonksiyonu 3. pin seçildigi için EXTI3
	if((EXTI->PR & (1<<3))!=0){ //pending registerinin 3. biti kontrol ediliyor
	     GPIOC->BSRR|=(1<<13);
       EXTI->PR|=(1<<3); //interrupt tekrar kuruluyor
	}
}
int main(){
  RCC->APB2ENR|=(1<<4)|(1<<2)|1; //portc,porta ve alternate function aktif yapilir
	GPIOA->CRL|=(1<<15); //porta 3. pin pull-down ve giris olarak ayarlandi
	GPIOA->CRL&=~((1<<12)|(1<<13)|(1<<14));
  
	AFIO->EXTICR[0] &=~((1<<12)|(1<<13)|(1<<14)|(1<<15));//portA nin 3. pini seçildi (EXTI3)
	
	GPIOC->CRH|=((1<<20)|(1<<21));
	GPIOC->CRH&=~((1<<22)|(1<<23));//portc 13. pin 50Mhz çikis olarak ayarlandi
	
	EXTI->FTSR|=(1<<3);//düsen kenar tetikleme ayarlandi
	EXTI->RTSR|=(1<<3);//yükselen kenar tetikleme ayarlandi
	EXTI->IMR|=(1<<3);//Interrupt mask register 3. hat için ayarlandi            #define  EXTI_IMR_MR3     ((uint32_t)0x00000008)     /*!< Interrupt Mask on line 3 */
	NVIC_EnableIRQ(EXTI3_IRQn);//Interrupt fonksiyonu aktif yapildi
	while(1){//main fonksiyonunda hiçbir islem yapilmiyor
	}
}
