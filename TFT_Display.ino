
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>

MCUFRIEND_kbv tft;

// Common MCUFRIEND resistive-touch pin arrangement
#define YP A1
#define XM A2
#define YM 7
#define XP 6

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Touch calibration values: adjust for your shield
#define TS_MINX 120
#define TS_MAXX 900
#define TS_MINY 70
#define TS_MAXY 920

#define BLACK   0x0000
#define WHITE   0xFFFF
#define BLUE    0x001F
#define SKY     0x5DDF
#define GREY    0x8410
#define CYAN    0x07FF
#define GREEN   0x07E0
#define ORANGE  0xFD20

bool startMenu = false;
int currentPage = 0;

void drawButton(int x, int y, int w, int h,
                uint16_t color, const char *label) {
  tft.fillRoundRect(x, y, w, h, 5, color);
  tft.drawRoundRect(x, y, w, h, 5, WHITE);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(x + 8, y + (h - 16) / 2);
  tft.print(label);
}

void drawDesktop() {
  tft.fillScreen(BLUE);

  // Desktop background
  tft.fillRect(0, 0, 320, 205, SKY);
  tft.fillCircle(250, 65, 35, CYAN);

  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(18, 20);
  tft.print("My Windows");

  tft.setTextSize(2);
  tft.setCursor(20, 82);
  tft.print("Arduino Desktop");

  // Desktop shortcuts
  drawButton(18, 120, 90, 45, BLUE, "Files");
  drawButton(120, 120, 90, 45, GREEN, "About");

  // Taskbar
  tft.fillRect(0, 205, 320, 35, BLACK);
  drawButton(5, 208, 95, 29, BLUE, "START");

  tft.setTextSize(1);
  tft.setCursor(225, 220);
  tft.setTextColor(WHITE);
  tft.print("MEGA OS");
}

void drawStartMenu() {
  tft.fillScreen(BLACK);

  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(20, 15);
  tft.print("Start");

  drawButton(20, 65, 280, 40, BLUE, "Files");
  drawButton(20, 115, 280, 40, GREEN, "Settings");
  drawButton(20, 165, 280, 40, ORANGE, "About");
  drawButton(20, 215, 100, 22, GREY, "Back");
}

void drawPage(const char *title, const char *message) {
  tft.fillScreen(BLUE);

  tft.fillRect(0, 0, 320, 45, BLACK);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 13);
  tft.print(title);

  tft.setTextSize(2);
  tft.setCursor(15, 85);
  tft.print(message);

  drawButton(10, 195, 100, 35, GREY, "Home");
}

void handleTouch() {
  TSPoint p = ts.getPoint();

  // Restore TFT control pins after reading touch
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z < 100 || p.z > 1000) return;

  // Common landscape mapping; calibration may be needed
  int x = map(p.y, TS_MINY, TS_MAXY, 0, 320);
  int y = map(p.x, TS_MINX, TS_MAXX, 0, 240);

  if (x < 0 || x >= 320 || y < 0 || y >= 240)
    return;

  if (currentPage != 0) {
    if (y > 185) {
      currentPage = 0;
      drawDesktop();
    }
    return;
  }

  if (startMenu) {
    if (y > 55 && y < 110) {
      currentPage = 1;
      drawPage("Files", "No files yet");
    } else if (y > 110 && y < 160) {
      currentPage = 2;
      drawPage("Settings", "Arduino Mega");
    } else if (y > 160 && y < 210) {
      currentPage = 3;
      drawPage("About", "Mini Windows OS");
    } else if (y > 210) {
      startMenu = false;
      drawDesktop();
    }
  } else {
    if (y > 200 && x < 110) {
      startMenu = true;
      drawStartMenu();
    } else if (y > 110 && y < 175 && x < 110) {
      currentPage = 1;
      drawPage("Files", "No files yet");
    } else if (y > 110 && y < 175 && x < 220) {
      currentPage = 3;
      drawPage("About", "Mini Windows OS");
    }
  }

  delay(250);
}

void setup() {
  Serial.begin(9600);

  uint16_t ID = tft.readID();
  Serial.print("TFT controller ID: 0x");
  Serial.println(ID, HEX);

  if (ID == 0xD3D3 || ID == 0x0000)
    ID = 0x9341;  // Fallback for some shields only

  tft.begin(ID);
  tft.setRotation(1);
  drawDesktop();
}

void loop() {
  handleTouch();
}