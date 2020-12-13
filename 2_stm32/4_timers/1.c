#include "stm32f10x.h"
//////////****** Örnek 1 Temel Bekleme Yaptirma  **********////////
// SR yi 0 ladik  while(!(TIM1->SR & 1)); ile 1 olana kadar bekliyoruz
// tasma oldugunda sr 1 oluyo ve while 0 laniyo
// dolayisiyla tasma olana kadar while içinde bekliyoruz
// sonradan tekrar 0 layip while 1 de kalmasini sagliyoruz

int main(){
	RCC->APB2ENR|=(1<<11); 	// timer1 Enable
	
	TIM1->SR =0; 						// set flag to 0
	TIM1->ARR=7200;					//auto reload register 2KHz
	TIM1->PSC=0;						//prescaler 
	TIM1->CCR1=1;						//duty cycl %10
	TIM1->CR1|=1;						//timer start
	
	while(1){
		while(!(TIM1->SR & 1));
		TIM1->SR =0; 								
	}
}

///////////********* Örnek 2 Timer interrupt fonksiyonu *******/////////

#include "stm32f10x.h"
void TIM1_UP_IRQHandler(){
	if(TIM1->SR&1){
		TIM1->SR=~1;//Tekrar aktif olmasi için
		//sonra interrupt ile yapilmak istenenler	
	}
}
int main2(){
	RCC->APB2ENR|=(1<<4); //portc enable
	GPIOC->CRH |=(3<<20);
	GPIOC->CRH &=~(3<<22);
	
	RCC->APB2ENR|=(1<<11); //timer enable
	TIM1->ARR=3600;
	TIM1-> PSC=9999;
	TIM1->RCR=0;// Ilk tasmada interrupti çagiriyo gecikme için 1++
	TIM1->DIER|=1; //	
	NVIC->ISER[0]|=(1<<25); //kütüphanedeki fonksiyonun sirasi
	TIM1->CR1|=1; //timer start;
	while(1){}		
}

////////**********timer ile PWM ********////////
#include "stm32f10x.h"
int main3(){
	RCC->APB2ENR|=(1<<2)|1; //alternatif fonk enable
	GPIOA->CRH&=~(1<<2);    //pini pwm için çikis
	GPIOA->CRH|=(1<<3)|3;
	
	RCC->APB2ENR|=(1<<11);//timer enable
	TIM1->CCMR1|=(6<<4);// pwmi vercemiz pini ayarlamak
	TIM1->BDTR|=(1<<15);//
	TIM1->ARR=3600;
	TIM1->PSC=0;
	TIM1=CCR1=360;//duty cycle %10
	TIM1=CR1|=1; //timer start
	while(1){}
}
