#include "stm32f10x.h"

/* Algoritmasi*/

/*1 saniyeyi 10'a böldüm. Her 0,1 snde SysTick_Handler interuptini çagiriyourum. */
/*10 kere interrupt oldugundan artma(val) degerini  360 arttiriyorum*/
//360+360+360.....360 =3600'a  1 sn içinde ++360 ile ulasmis oluyoruz
/*0'dan 3600'a ve tersi için ise yön degiskenini kullaniyorum */

/*Dolayisiyla 1 saniye içinde ledi %100 ve 1 sn içinde %0 parlakliga ayarlliyorum*/

/*note daha hassas arttirma/azaltma ayarlanabilir *  ++18,72Mhz/1600 gibi */



int duty_cycle=0;		//duty cycle 0-3600
int yonu=1; 				/* if yönü==1 => 0---->3600   
										   if yönü==0 => 3600---->0  */ 
int val =360;				// interrupt artma degeri


int arttir(){
	duty_cycle += val;
	TIM1->CCR2=duty_cycle;
	if(duty_cycle == 3600) {yonu=0;}
}
int azalt(){
	duty_cycle -= val;
	TIM1->CCR2=duty_cycle;
	if(duty_cycle == 0)  {yonu=1;}
}

void SysTick_Handler(void){
	if(yonu==1){arttir();}
	if(yonu==0){azalt();}
	}

	
int main(){
	RCC->APB2ENR|=(1<<2)|1;//portA->enable,AFIO
	RCC->APB2ENR|=(1<<11);//TIM1->enable
	
	GPIOA->CRH&=~(1<<6);// PA9->Mode(output),CNF(push-pull)
  GPIOA->CRH|=(1<<7)|(1<<5)|(1<<4);
	
	TIM1->CCER |= (1<<4);// Channel2->Output enable
	TIM1->CCMR1|=(6<<12);//ccmr1-> PWMmode1 (6=110)
	TIM1->BDTR |= (1<<15); //Break and dead-time register. Main output enable
	TIM1->ARR=3600 ;//auto reload register 2KHz
	TIM1->PSC=10;//prescaler 
  TIM1->CCR2=0;//Channel 2 için duty cycl=%0 
	TIM1->CR1|=1;	//Counter enable
	
	SysTick -> LOAD =72000000 /80;  //0,1sn =100ms
	SysTick -> CTRL=SysTick_CTRL_ENABLE_Msk|SysTick_CTRL_TICKINT_Msk;
	while(1){}
}
