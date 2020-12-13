int kontrol;																								// ledi kontrol için kullanilacak
#include "stm32f10x.h"


void SysTick_Handler(void){																  //interruptun çalistirdigi ledi kontrol eden fonk
	if (kontrol==1){
		kontrol =0;
		GPIOC -> BSRR |= (1<<13);														   	//ilgili ODRx bitini sifirla
	}
	else{
		kontrol = 1;
		GPIOC -> BSRR |=(1<<(13+16));													  //ilgili ODRx bitini set et
	 }
	}

	
void EXTI15_10_IRQHandler(void){ 														//interrupt fonksiyonu 14. pin seçildigi için 10-15 arasi pinlere uygun fonk = EXTI15_10_IRQHandler
	if((EXTI->PR & (1<<14))!=0){ 															//seçilen kenar eventi gelince PR14 1 olcak. 1 ile kontrol ediyoroz. 
	     SysTick -> LOAD =RCC_CFGR_MCO_SYSCLK/80;							//72Mhz/80= 900.000 == 11011011101110100000 bu degeri load registerina yüklüyoruz asagi saymaya baslicak 0 oldugunda 0.1sn geçmis olcak 10Hz=0,1sn
			 SysTick->CTRL=SysTick_CTRL_ENABLE_Msk|SysTick_CTRL_TICKINT_Msk;  // ilgili enable maskeleri
       EXTI->PR|=(1<<14);																		//interrupt tekrar kuruluyor (bunun amacini anlamadim?)
	}	
}
int main(){
  RCC->APB2ENR|=(1<<4)(1<<2)|1; 													  //portc, porta ve alternate function aktif yapilir
	GPIOC->CRH|=(1<<27); 																			//portC 14. pin pull-down ve giris olarak ayarlandi
	GPIOC->CRH&=~((1<<26)|(1<<25)|(1<<24));										//portC 14. pin pull-down ve giris olarak ayarlandi
	AFIO->EXTICR[3] &=~((1<<11)|(1<<10)|(1<<8));							//portC nin 14. pini seçildi (EXTI15_10_IRQHandler)  #define AFIO_EXTICR4_EXTI13_PC               ((uint16_t)0x0020)            /*!< PC[13] pin */
	AFIO->EXTICR[3] |=(1<<9);				

	
	
	GPIOA->CRL|=(1<<0)|(1<<1); //pa0 mode output
	GPIOA->CRL&=~((1<<3)|(1<<2));	//pa0 cnf													//portc 13. pin 50Mhz çikis olarak ayarlandi
	
	GPIOA->CRL|=(1<<4)|(1<<5); //pa1 mode output
	GPIOA->CRL&=~((1<<7)|(1<<6));	//pa1 cnf
	
	GPIOA->CRL|=(1<<9)|(1<<8); //pa2 mode output
	GPIOA->CRL&=~((1<<11)|(1<<10));	//pa2 cnf
	
	GPIOA->CRL|=(1<<13)|(1<<12); //pa3 mode output
	GPIOA->CRL&=~((1<<15)|(1<<14));	//pa3 cnf
	
	GPIOA->CRL|=(1<<17)|(1<<16); //pa4 mode output
	GPIOA->CRL&=~((1<<19)|(1<<18));	//pa4 cnf
	
	GPIOA->CRL|=(1<<21)|(1<<20); //pa5 mode output
	GPIOA->CRL&=~((1<<23)|(1<<22));	//pa5 cnf
	
	GPIOA->CRL|=(1<<25)|(1<<24); //pa6 mode output
	GPIOA->CRL&=~((1<<27)|(1<<26));	//pa6 cnf
	
	GPIOA->CRL|=(1<<29)|(1<<28); //pa7 mode output
	GPIOA->CRL&=~((1<<31)|(1<<30));	//pa7 cnf
	
	
	EXTI->FTSR|=(1<<14);																			//düsen kenar tetikleme ayarlandi
	EXTI->RTSR|=(1<<14);																			//yükselen kenar tetikleme ayarlandi
	EXTI->IMR|=(1<<14);																				//Interrupt mask register 3. hat için ayarlandi            #define  EXTI_IMR_MR3     ((uint32_t)0x00000008)     /*!< Interrupt Mask on line 3 */
	NVIC_EnableIRQ(EXTI15_10_IRQn);														//Uygn Interrupt fonksiyonu aktif yapildi
	
	
	while(1){																									//sonsuz dongu interrupt olusturacaz.
	}
}
