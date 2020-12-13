
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define DQ 2
int ok,command,i,data[9],j,derece,sing;
unsigned int a ;

void setup() {
  pinMode(DQ,INPUT);
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
  display.setTextSize(5);
  display.setTextColor(SSD1306_WHITE);
}
void sicaklik(){
  ////////////HESAPLAMALAR//////////
  a=65535;
  a = a&data[1];
  a = a<<8;
  a = a|data[0];
  Serial.println(a);
  /*[s][s][s][s][s]_[x][x][x][x][x][x][x].[x][x][x][x]*/
  /*[0][0][0][0][0]_[1][1][1][1][1][1][1].[0][0][0][0]*/
  derece =  2032; //11111110000
  sing   = 63488; //1111100000000000
  sing   = sing >>11;
  /*if sing =! 0 ==> sing - else +*/
  derece = derece & a;
  derece = derece>>4;
  Serial.print("derece=");
  Serial.println(derece);
  
  /////////////EKRANA YAZDIRMA////////////
  display.setTextSize(5);
  display.setCursor(0,16);
  if(sing =!0){
    display.print("+");
    }
  else{
    display.print("-");
    derece = 127-derece; //tümleyeni
    }
  display.print(derece);
  display.print("C");
  display.setTextSize(1);
  display.print("*");
  
  display.display();
  display.clearDisplay();
delay(1000);
  
}

void writeBit(int b){
  if(b){
    pinMode(DQ,OUTPUT);
    digitalWrite(DQ,LOW);
    delayMicroseconds(1);
    pinMode(DQ,INPUT);
    delayMicroseconds(60);
    
    }
    else{
    pinMode(DQ,OUTPUT);
    digitalWrite(DQ,LOW);
    delayMicroseconds(60);
    pinMode(DQ,INPUT);
    delayMicroseconds(5);
    }
  }


int readBit(){
  pinMode(DQ,OUTPUT);
  digitalWrite(DQ,LOW);
  delayMicroseconds(1);
  pinMode(DQ,INPUT);
  delayMicroseconds(5);
  ok=digitalRead(DQ);
  delayMicroseconds(80);
  return ok;
  }
void reset_pulse(){
  pinMode(DQ,OUTPUT);
  digitalWrite(DQ,LOW);
  delayMicroseconds(500);
  }
void presence_pulse(){
  pinMode(DQ,INPUT);
  delayMicroseconds(500);
  }
  
void Command(int i){
  command = i;
  for(i=0;i<8;i++){
    writeBit(command&0x01);
    command>>=1;
    }
  }
    



void loop() {
  reset_pulse();
  presence_pulse();
  Command(0xCC);//tek sensor oldugu için rom okunmadı.

  Command(0x44);//Ölçüm yap ve kaydet.

  reset_pulse();
  presence_pulse();
  Command(0xCC);


  Command(0xBE);//Bellekten data  oku
  for(j=0;j<9;j++){
    data[j]=0;
    for(i=0;i<8;i++){
     data[j]>>=1;
     data[j]|=(readBit()<<7);
     }
    }
    sicaklik();
}
