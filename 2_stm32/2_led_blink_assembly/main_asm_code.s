	AREA deneme, code
	EXPORT __main
__main
	
	MOV32 R0,#0x40021000 ;APB2ENR biriminin RCC reg'inin baslangi� adresi.
	LDR R1, [R0,#0x18]   ;RCC_APB2ENR offset adresini R1 degine set ettim.
	ORR R1,#(1<<4)		 ;GPIO port C aktif olmasi(clock sinyali verilmesi) i�in 4. bitini 1 setleyecek maske
	STR R1,[R0,#0x18]	 ;R1 maskesini RCC_APB2ENR regine storeladim.(y�kledim) Portc aktif oldu.
	
	
	MOV32 R0,#0x40011000 ;GPIO port c adresi.
	LDR R1, [R0,#0x04]	 ;GPIOx_CRH offset adresi 
	ORR R1,#(1<<21)		 ;MODE13 i�in 01 maskesi (general output mode)
	AND R1,#~(1<<22)	 ;MODE13 i�in 01 maskesi (general output mode)
	STR R1,[R0,#0x04]    ;R1 maskesini GPIOx_CRH offset adresine y�kl�yoruz ve port13 output ayarlaniyor.
						 ;C portlarinin clock sinyalini a�tigimiz i�in portC 13. pini output ayarlandi.
		
	
	
loop
	LDR R1,[R0,#0x0C]    ;GPIOx_ODR offset adresi (�ikis degerini high veya low ayarlamak i�in kullanilir.)
	ORR R1,#(1<<13)		 ;13. pini high setleyecek maske (portc13 led ters baglantili o y�zden highda s�n�yor.) 
	STR R1,[R0,#0x0C]    ;R1 maskesini GPIOx_ODR offset adresine y�kl�yoruz ve portc13 pin i�in ODR'in 13. biti 1 setlendi (led off)
	
	
	MOV R3,#0x0 		 ;i		
	MOV R4,#0x0 		 ;sum
	MOV R5,#0x250000 	 ;limit yaklasik 1 sn i�in

FORLOOP       			 ;for(i=0; i<25000; i++){if(i==limit){return} sum+=1; i+=sum;}
	CMP R3,R5  			 ;r3 ve r5 degerleri esit olana kadar arttirma islemi yapiyorum eger cmp'dan esitlik �ikarsa BEQ ile endlopa dallaniyorum.
	BEQ endloop 		 ;eger R3 == R5 ise endloop'a git(dallanma)
	ADD R4,R4,#1		 ;sum +=1
	ADD R3,R3,R4		 ;i +=sum
	B FORLOOP 			 ;foorlopa git
endloop
	
	LDR R1,[R0,#0x0C]
	AND R1,#~(1<<13)
	STR R1,[R0,#0x0C]    ;LED ON

;ikinci delay i�in regleri sifirliyorum ayni islemler tekrar yapiliyor.
	MOV R3,#0x0 ;i
	MOV R4,#0x0 ;sum
	MOV R5,#0x250000
FORLOOP2
	CMP R3,R5
	BEQ endloop2
	ADD R4,R4,#1
	ADD R3,R3,R4
	B FORLOOP2
endloop2	

	B loop
	END