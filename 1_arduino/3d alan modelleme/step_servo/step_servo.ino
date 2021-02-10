#include <Servo.h>
Servo servo;
#define COIL1 8
#define COIL2 9
#define COIL3 10
#define COIL4 11
int i,j,k,r,temp,angle;


int trigPin = 7; /* Sensorun trig pini Arduinonun 6 numaralı ayağına bağlandı */
int echoPin = 6;  /* Sensorun echo pini Arduinonun 7 numaralı ayağına bağlandı */
float sure;
float uzaklik;


void setup() {
  pinMode(COIL1,OUTPUT);
  pinMode(COIL2,OUTPUT);
  pinMode(COIL3,OUTPUT);
  pinMode(COIL4,OUTPUT);
  
  servo.attach(3);
  
  pinMode(trigPin, OUTPUT); /* trig pini çıkış olarak ayarlandı */
  pinMode(echoPin,INPUT); /* echo pini giriş olarak ayarlandı */
  Serial.begin(9600); /* Seri haberlesme baslatildi */
}

///////////////////STEP//////////////////////
void Step_clock_NO_direction(){
  digitalWrite(COIL1,LOW);
  digitalWrite(COIL2,LOW);
  digitalWrite(COIL3,LOW);
  digitalWrite(COIL4,HIGH);
  delay(5);
    
  digitalWrite(COIL1,LOW);
  digitalWrite(COIL2,LOW);
  digitalWrite(COIL3,HIGH);
  digitalWrite(COIL4,LOW);
  delay(5);
  
  digitalWrite(COIL1,LOW);
  digitalWrite(COIL2,HIGH);
  digitalWrite(COIL3,LOW);
  digitalWrite(COIL4,LOW);
  delay(5);
  
  digitalWrite(COIL1,HIGH);
  digitalWrite(COIL2,LOW);
  digitalWrite(COIL3,LOW);
  digitalWrite(COIL4,LOW);
  delay(5);
  }
void Step_clock_direction(){
  digitalWrite(COIL1,HIGH);
  digitalWrite(COIL2,LOW);
  digitalWrite(COIL3,LOW);
  digitalWrite(COIL4,LOW);
  delay(5);
    
  digitalWrite(COIL1,LOW);
  digitalWrite(COIL2,HIGH);
  digitalWrite(COIL3,LOW);
  digitalWrite(COIL4,LOW);
  delay(5);
  
  digitalWrite(COIL1,LOW);
  digitalWrite(COIL2,LOW);
  digitalWrite(COIL3,HIGH);
  digitalWrite(COIL4,LOW);
  delay(5);
  
  digitalWrite(COIL1,LOW);
  digitalWrite(COIL2,LOW);
  digitalWrite(COIL3,LOW);
  digitalWrite(COIL4,HIGH);
  delay(5);
  }

   
void mesafe(){
  digitalWrite(trigPin, LOW); /* sensör pasif hale getirildi */
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); /* Sensore ses dalgasının üretmesi için emir verildi */
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  /* Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi */ 
  sure = pulseIn(echoPin, HIGH); /* ses dalgasının geri dönmesi için geçen sure ölçülüyor */
  uzaklik= (sure /28.5)/2; /* ölçülen sure uzaklığa çevriliyor */ 
   if(uzaklik > 400)
   uzaklik = 400;
  }



void scan(){
  for(i=0; i<36;i++){
    for(j=0;j<=180;j+=5){
      servo.write(j);
      delay(40);
      mesafe();
   
      Serial.print(i);
      Serial.print(" ");
      Serial.print(j);
      Serial.print(" ");
      Serial.println(uzaklik);
      }
   
    for(k=0; k<7;k++){       //4.921* derece step saat yönünde 
      Step_clock_NO_direction();
    }
    for(temp=180; temp>0; temp-=10){
      servo.write(temp);
      delay(40);
    }
  }   
  

  //for reset pos  step motor
  for(j=0;j<36;j++){
    for(i=0; i<7;i++){//4.921* derece
      Step_clock_direction();
    }
  }
 
}

void loop() {
 delay(5000);
 
 servo.write(0); 
 delay(300);
 scan();
 delay(10);
 while(1){
  }
}
