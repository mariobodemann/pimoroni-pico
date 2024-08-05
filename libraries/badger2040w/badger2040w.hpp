#pragma once

#include <string>
#include <memory>

#include "drivers/uc8151/uc8151.hpp"
#include "drivers/pcf85063a/pcf85063a.hpp"
#include "pico/cyw43_arch.h"
#include "cyw43.h"
#include "libraries/pico_graphics/pico_graphics.hpp"


namespace pimoroni {

  class Badger2040W {
  protected:
    uint32_t _button_states = 0;
    uint32_t _wake_button_states = 0;
    std::unique_ptr<UC8151> display;
    std::unique_ptr<PicoGraphics_Pen1BitY> graphics;
    std::unique_ptr<PCF85063A> rtc;
    cyw43_t wifi;

  private:
    void imageRow(const uint8_t *data, Rect rect);

  public:
    uint DISPLAY_WIDTH = 296;
    uint DISPLAY_HEIGHT = 128;

    Badger2040W(){};
    void setup();
    void update();
    void partial_update(Rect region);
    void halt();

    // state
    void led(uint8_t brightness);

    // inputs (buttons: A, B, C, D, E, USER)
    bool pressed(uint8_t button);
    bool pressed_to_wake(uint8_t button);
    void wait_for_press();
    void update_button_states();
    uint32_t button_states();

    // drawing
    void clear(bool white);
    void drawRectangle(int x, int y, int w, int h, bool white);

    void drawText();

    void drawImage(const uint8_t *data);
    void drawImage(const uint8_t *data, Rect rect);

    // wifi
    int startWifiScan();
    cyw43_ev_scan_result_t wifiGetScanResult();
    bool isScanningWifi();
    int wifiStatus();

    void wifiLedOn(bool on);

  public:
    enum pin {
      RTC         = 8,
      A           = 12,
      B           = 13,
      C           = 14,
      D           = 15,
      E           = 11,
      UP          = 15, // alias for D
      DOWN        = 11, // alias for E
      CS          = 17,
      CLK         = 18,
      MOSI        = 19,
      DC          = 20,
      RESET       = 21,
      BUSY        = 26,
      VBUS_DETECT = 24,
      LED         = 22,
      BATTERY     = 29,
      ENABLE_3V3  = 10
    };

  };

}
