/* SoftwareSerial +OLED+ MQTT receive sample. (Atmega328P )
*/

#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

SoftwareSerial mySerial(5, 6); /* RX:D5, TX:D6 */
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };
  
//
void setup() {
  Serial.begin( 9600 );
  mySerial.begin( 9600 );
  Serial.println("#Start-setup-SS");
    //
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display();
  delay(2000);
  display.clearDisplay(); 
}
//
void display_OLED(String sNum ){
  //sTmp="Temp:"+ sTmp+ " C";
  display.setTextSize(2);
  display.setCursor(0,0);
  display.setTextColor(WHITE);
  display.println( "Count:" );
  display.println( sNum );
  display.display();
  delay(500);  
  display.clearDisplay();
}
//
boolean Is_validHead(String sHd){
  boolean ret=false;
  if(sHd=="d1"){
    ret= true;
  }else if(sHd=="d2"){
    ret= true;
  }
  return ret;
}
String mBuff="";
//
void loop() {
    while( mySerial.available() ){
      char c= mySerial.read();
      mBuff.concat(c );
      if(  mBuff.length() >= 10 ){
        String sHead= mBuff.substring(0,2);
        boolean bChkHd= Is_validHead( sHead );
        if(bChkHd== true){
          Serial.println( "Hd="+ sHead );
          Serial.println( "mBuff="+ mBuff );
          String sTmp= mBuff.substring(2,10);
          int iNum=sTmp.toInt();
          sTmp= String(iNum);
          display_OLED(sTmp );
        }        
        mBuff="";
      }
    }

}




