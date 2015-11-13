#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

uint16_t DspWidth = 0;
uint16_t DspHeight = 0;

void setup() {
  Serial.begin(9600);
  Serial.println(F("DZM-Test"));
  
  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();
  tft.begin(0x9341);
  tft.fillScreen(BLACK);
  DspWidth = 320;
  DspHeight = tft.height();
  
}

void loop() {

  uint16_t alpha;

  tft.fillCircle(0, DspWidth/2, DspWidth/2-2, RED);
  tft.drawCircle(0, DspWidth/2, DspWidth/2-1, WHITE);
  
  for(alpha = 0; alpha < 180; alpha++ )
  {    
    

    uint16_t xValue = sin(alpha)*(DspWidth/2-2);
    uint16_t yValue = cos(alpha)*(DspWidth/2-2) + DspWidth/2;
      
    Serial.print("x-Wert ");
    Serial.print(xValue);
    Serial.print("\ty-Wert: ");
    Serial.print(yValue);
    Serial.print("\talpha: ");
    Serial.println(alpha);
    
    
    tft.drawLine(0, DspWidth/2, xValue, yValue, BLUE);
    delay(500);
  }

}
