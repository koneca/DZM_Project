#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin


// The pin for the potentiometer
#define POTI A4

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

uint16_t xaxis[181] = { 0, 3, 6, 8, 11, 14, 17, 19, 22, 25, 27, 30, 33, 36, 38, 41, 44, 46, 49, 51, 54, 57, 59, 62, 64, 67, 69, 72, 74, 77, 79, 81, 84, 86, 88, 91, 93, 95, 97, 99, 102, 104, 106, 108, 110, 112, 114, 116, 117, 119, 121, 123, 125, 126, 128, 129, 131, 133, 134, 135, 137, 138, 140, 141, 142, 143, 144, 145, 146, 148, 148, 149, 150, 151, 152, 153, 153, 154, 155, 155, 156, 156, 156, 157, 157, 157, 158, 158, 158, 158, 158, 158, 158, 158, 158, 157, 157, 157, 156, 156, 156, 155, 155, 154, 153, 153, 152, 151, 150, 149, 148, 148, 146, 145, 144, 143, 142, 141, 140, 138, 137, 135, 134, 133, 131, 129, 128, 126, 125, 123, 121, 119, 117, 116, 114, 112, 110, 108, 106, 104, 102, 99, 97, 95, 93, 91, 88, 86, 84, 81, 79, 77, 74, 72, 69, 67, 64, 62, 59, 57, 54, 51, 49, 46, 44, 41, 38, 36, 33, 30, 27, 25, 22, 19, 17, 14, 11, 8, 6, 3, 0};
uint16_t yaxis[181] = { 2, 2, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 6, 7, 7, 8, 9, 10, 11, 12, 12, 14, 15, 16, 17, 18, 19, 20, 22, 23, 25, 26, 27, 29, 31, 32, 34, 35, 37, 39, 41, 43, 44, 46, 48, 50, 52, 54, 56, 58, 61, 63, 65, 67, 69, 72, 74, 76, 79, 81, 83, 86, 88, 91, 93, 96, 98, 101, 103, 106, 109, 111, 114, 116, 119, 122, 124, 127, 130, 133, 135, 138, 141, 143, 146, 149, 152, 154, 157, 160, 163, 166, 168, 171, 174, 177, 179, 182, 185, 187, 190, 193, 196, 198, 201, 204, 206, 209, 211, 214, 217, 219, 222, 224, 227, 229, 232, 234, 237, 239, 241, 244, 246, 248, 251, 253, 255, 257, 259, 262, 264, 266, 268, 270, 272, 274, 276, 277, 279, 281, 283, 285, 286, 288, 289, 291, 293, 294, 295, 297, 298, 300, 301, 302, 303, 304, 305, 306, 308, 308, 309, 310, 311, 312, 313, 313, 314, 315, 315, 316, 316, 316, 317, 317, 317, 318, 318, 318, 318};

int gaugeVal;
int oldGaugeVal;

void setup() {
 // Serial.begin(9600);
//  Serial.println(F("DZM-Test"));

 // Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();
  tft.begin(0x9341);
  tft.fillScreen(BLACK);
  DspWidth = 320;
  DspHeight = tft.height();
}

void loop() {

  int alpha;

  tft.drawCircle(0, DspWidth/2, DspWidth/2-1, WHITE);
  tft.fillCircle(0, DspWidth/2, DspWidth/2-2, RED);

  val = analogRead(potPin);    // read the value from the sensor
  
  for(alpha = 0; alpha <= 3200; alpha += 10 )
  {
    drawGauge(alpha);
  }

  tft.drawCircle(0, DspWidth/2, DspWidth/2-1, WHITE);
  tft.fillCircle(0, DspWidth/2, DspWidth/2-2, RED);

  for(alpha = 3200; alpha >= 0; alpha -= 10 )
  {
    drawGauge(alpha);
  }
}

void drawGauge(uint16_t alpha)
{
  tft.setTextColor(GREEN);  tft.setTextSize(4);
  tft.setRotation(1);
  tft.setCursor(10,10);
  tft.fillRect(10,10,93,28, BLACK);
  tft.println(alpha);

  tft.setRotation(0);
  oldGaugeVal = gaugeVal;
  gaugeVal = map(alpha, 0, 3200, 0, 180);

  if(oldGaugeVal < gaugeVal)
  {
    if(1 < gaugeVal )
    tft.drawLine(0, DspWidth/2, xaxis[gaugeVal-2], yaxis[gaugeVal-2], RED);
  }
  else
  {
    if(180 != gaugeVal )
    {
      tft.drawLine(0, DspWidth/2, xaxis[gaugeVal+2], yaxis[gaugeVal+2], RED);
    }
    else
    {
       tft.drawLine(0, DspWidth/2, xaxis[gaugeVal], yaxis[gaugeVal], RED);
    }
  }
  tft.drawLine(0, DspWidth/2, xaxis[gaugeVal], yaxis[gaugeVal], YELLOW); 
}

