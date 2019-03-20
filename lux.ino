#include <Wire.h>              
#include <SPI.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
#define ledPin1 D0    

Adafruit_SSD1306 OLED(OLED_RESET);

int BH1750address = 0x23;      
byte buff[2];
void setup() 
{
   pinMode(ledPin1, OUTPUT); 
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3c);
}

void loop() 
{
  uint16_t val = 0;
  BH1750_Init(BH1750address);             
  delay(200);
  if (2 == BH1750_Read(BH1750address))   
  {
    val = ((buff[0] << 8) | buff[1])/1.2;
    OLED.clearDisplay();
    OLED.setTextColor(WHITE);
    OLED.setCursor(0,0);
    OLED.setTextSize(3);
    OLED.println("BH1750");
    OLED.setCursor(0,35);
    OLED.println(String(val)+"1x");
    OLED.display();
    
  }
  
  delay(150);
 if (BH1750address>500)
 {digitalWrite(ledPin1, 1);}
}
int BH1750_Read(int address)             
{
  int i = 0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while (Wire.available())
  {
    buff[i] = Wire.read();                
    i++;
  }
  Wire.endTransmission();
  return i;


}
void BH1750_Init(int address)             
{
  Wire.beginTransmission(address);
  Wire.write(0x10);                       
  Wire.endTransmission();

}
