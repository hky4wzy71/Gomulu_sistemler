#include "stm32f10x.h"

int main(void){
	RCC -> APB2ENR |= (1<<4); 	
	// reset clock control(RCC) ile clock veya resetini kontrol ediyoruz.
	// RCC_APB2ENR registeri ile de portlarin clocklarini ayarlicaz.
  // APB2ENR, 00000000000000000000000000000000	 32 bit  bu regin 4. bitini 1 yaparsak c portunun clocku aktif hale gelcek.
	// (1<<4),  00000000000000000000000000001000   bu maske ile 4. bite yazdirmaya çalisiyoruz (stmManuel 133sayfa) 
	//          00000000000000000000000000001000 or ile 4. bite 1 setlemis olduk artik c portunun clksi aktif
	
	
	GPIOC -> GPIOC -> CRH &= ~((1<<23)|(1<<22)); 
	//port c aktif hale geldi artik 13.pini aktif yapalim.GPIOC ile genel i/o controlunu yapiyouz.
  // CRH ise 8-15 arasi  bitleri kontrol ediyo 13.pin için crh kullancaz.
	//CRHta mode var bide cnf(control fonksiyon) var mode 23 22 ile cnf ayarliyoruz. mode output için 00 push-pull output yapcaz.
	// 13.pinin cnfsini ayarliyalim.
	//crh,      00000000000000000000000000000000
	//(1<<23),  00000000100000000000000000000000 23. bitine 1 set etmek için maske
	//~((1<<23),11111111011111111111111111111111
	//CRH &= ~((1<<23), böylece 23.pini 0 lamis olduk
	
	
	GPIOC -> CRH |= ((1<<21)|(1<<20));
	// 13. pinin modunu ayarlayalim out put için 
	//21 ve 20yi 1 yapcaz (stmManuel'den yine bakilirsa)
	//CRH, 			00000000000000000000000000000000
	//(1<<21),	00000000010000000000000000000000
	//CRH |= ((1<<21) ile de 21. pine 1 set etmis olduk 
while(1){
	
	GPIOC ->ODR |= (1<<13);
	//Output Data regin(ODR) ile çikisi kontrol ediyoruz bizim led 13. pinde
	// (1<<13) maskesi ile 00000000000000000010000000000000 
	// ODR,								 00000000000000000000000000000000
	//ODR |= (1<<13) 			 00000000000000000010000000000000 set etmis olduk 13. pine 3.3 volt vercek artik.
	for(int i = 0; i<1000000; i++); // burda saydirma yapip ufak bi bekleme sagliyoruz.
	
	GPIOC->ODR &= (0<<13);  //GPIOC -> ODR |=~(1<<13); yine ayni sekilde 3.3 voltu 0'liyoruz led sonuyo.
	for(int i = 0; i<1000000; i++);
	}
}
