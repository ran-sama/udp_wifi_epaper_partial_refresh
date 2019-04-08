#include <WiFi.h>
#include "AsyncUDP.h"

#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold12pt7b.h>

GxEPD2_BW<GxEPD2_154, GxEPD2_154::HEIGHT> display(GxEPD2_154(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));

#include "ran.h"

char ssid[] = "mySSID";
char pass[] = "myWifiPass";

char *ptr;
int attempts = 0;
char delimiter[] = "$";
int myCount, lastUpdate, timePassed;

AsyncUDP udp;

void setup() {
  display.init();
  display.setFullWindow();
  display.setRotation(1);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold12pt7b);
  display.fillScreen(GxEPD_WHITE);
  display.display();
  display.drawInvertedBitmap(0, 0, gImage_ran, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
  display.display(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    attempts++;
      if (attempts >= 60) {
        ESP.restart();
      }
  }
  delay(200);
  display.setCursor(152, 128);
  display.print("UDP");
  display.display(true);
  delay(200);
  if (udp.listen(8888)) {
    udp.onPacket([](AsyncUDPPacket packet) {
    ptr = strtok((char*) packet.data(), delimiter);
    myCount = 0;
    while (ptr != NULL) {
      showPartialUpdate(String(ptr), myCount);
      ptr = strtok(NULL, delimiter);
      myCount += 1;
    }
    myCount = 0;
    display.fillRect(0, 198, display.epd2.WIDTH, 2, GxEPD_WHITE);
    display.display(true);
    lastUpdate = millis();
    });
  }
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    ESP.restart();
  }
  if (millis() >= 3600000) {
      ESP.restart();
  }
  timePassed = (millis() - lastUpdate) / 1000;
  if (timePassed >= 480) {
      ESP.restart();
  }
  delay(2000);
}

void showPartialUpdate(String sumBuf, int8_t cnt) {
  uint16_t box_x = 0;
  uint16_t box_y = 0 + (22 * cnt);
  uint16_t box_w = display.epd2.WIDTH; //alternatively display.width()
  uint16_t box_h = 22;
  uint16_t cursor_y = box_y + 15;
  display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
  display.setCursor(0, cursor_y);
  display.print(sumBuf);
}
