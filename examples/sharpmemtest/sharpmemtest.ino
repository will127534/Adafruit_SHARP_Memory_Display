#include <Adafruit_GFX.h>
#include <SharpMem_8bit.h>

#define reset 28
#define rs 34
#define cs 29
#define wr 26
#define rd 25
#define ack 32
#define en 24
#define sync 33

Adafruit_SharpMem display(reset, rs, cs, wr, rd, ack, en, sync);

#define BLACK 0
#define WHITE 1
int minorHalfSize; // 1/2 of lesser of display width or height

void setup() {
  Serial.begin(9600);
  Serial.println("Hello!");

  // start & clear the display
  display.begin();
  display.clearDisplay();

  // Several shapes are drawn centered on the screen.  Calculate 1/2 of
  // lesser of display width or height, this is used repeatedly later.
  minorHalfSize = min(display.width(), display.height()) / 2;

  // draw many lines
  testdrawline();
  delay(500);
  display.clearDisplay();

  // draw rectangles
  testdrawrect();
  delay(500);
  display.clearDisplay();

  // draw multiple rectangles
  testfillrect();
  display.refresh();
  delay(500);
  display.clearDisplay();

  // draw a circle, 10 pixel radius
  display.fillCircle(display.width()/2, display.height()/2, 10, BLACK);
  display.refresh();
  delay(500);
  display.clearDisplay();

  testdrawroundrect();
  display.refresh();
  delay(500);
  display.clearDisplay();

  testfillroundrect();
  display.refresh();
  delay(500);
  display.clearDisplay();

  testdrawtriangle();
  display.refresh();
  delay(500);
  display.clearDisplay();

  testfilltriangle();
  display.refresh();
  delay(500);
  display.clearDisplay();

  testdrawchar();
  display.refresh();
  for(int i=0; i<4; i++) {
    display.refresh();
    delay(500);
  }
}

void loop(void) 
{
  for(int i=0; i<4; i++) {
    display.setRotation(i);
    display.clearDisplay();
    // text display tests
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(0,0);
    display.println("Hello, world!");
    display.setTextColor(WHITE, BLACK); // inverted text
    display.println(3.141592);
    display.setTextSize(2);
    display.setTextColor(BLACK);
    display.print("0x"); display.println(0xDEADBEEF, HEX);
    // Screen must be refreshed at least once per second
    for(int j=0; j<4; j++) {
      display.refresh();
      delay(500); // 1/2 sec delay
    } // x4 = 2 second pause between rotations
  }
}


void testdrawline() {
  for (int i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, BLACK);
    display.refresh();
  }
  for (int i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, BLACK);
    display.refresh();
  }
  delay(250);

  display.clearDisplay();
  for (int i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, BLACK);
    display.refresh();
  }
  for (int i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, BLACK);
    display.refresh();
  }
  delay(250);

  display.clearDisplay();
  for (int i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, BLACK);
    display.refresh();
  }
  for (int i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, BLACK);
    display.refresh();
  }
  delay(250);

  display.clearDisplay();
  for (int i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, BLACK);
    display.refresh();
  }
  for (int i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, BLACK);
    display.refresh();
  }
  delay(250);
}

void testdrawrect(void) {
  for (int i=0; i<minorHalfSize; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, BLACK);
    display.refresh();
  }
}

void testfillrect(void) {
  uint8_t color = BLACK;
  for (int i=0; i<minorHalfSize; i+=3) {
    // alternate colors
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, color&1);
    display.refresh();
    color++;
  }
}

void testdrawroundrect(void) {
  for (int i=0; i<minorHalfSize/2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i, minorHalfSize/2, BLACK);
    display.refresh();
  }
}

void testfillroundrect(void) {
  uint8_t color = BLACK;
  for (int i=0; i<minorHalfSize/2; i+=2) {
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i, minorHalfSize/2, color&1);
    display.refresh();
    color++;
  }
}

void testdrawtriangle(void) {
  for (int i=0; i<minorHalfSize; i+=5) {
    display.drawTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, BLACK);
    display.refresh();
  }
}

void testfilltriangle(void) {
  uint8_t color = BLACK;
  for (int i=minorHalfSize; i>0; i-=5) {
    display.fillTriangle(display.width()/2  , display.height()/2-i,
                         display.width()/2-i, display.height()/2+i,
                         display.width()/2+i, display.height()/2+i, color & 1);
    display.refresh();
    color++;
  }
}

void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.cp437(true);

  for (int i=0; i < 256; i++) {
    if (i == '\n') continue;
    display.write(i);
  }
  display.refresh();
}