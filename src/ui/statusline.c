#include "statusline.h"
#include "../driver/eeprom.h"
#include "../driver/st7565.h"
#include "../helper/battery.h"
#include "../scheduler.h"
#include "components.h"
#include "graphics.h"
#include <string.h>

static uint8_t previousBatteryLevel = 255;
static bool showBattery = true;

static bool lastEepromRead = false;
static bool lastEepromWrite = false;

static void eepromRWReset() {
  lastEepromRead = lastEepromWrite = gEepromRead = gEepromWrite = false;
}

void STATUSLINE_update() {
  BATTERY_UpdateBatteryInfo();
  if (gBatteryDisplayLevel) {
    if (previousBatteryLevel != gBatteryDisplayLevel) {
      previousBatteryLevel = gBatteryDisplayLevel;
      UI_Battery(gBatteryDisplayLevel);

      gRedrawScreen = true;
    }
  } else {
    showBattery = !showBattery;
    gRedrawScreen = true;
  }

  if (lastEepromRead != gEepromRead || lastEepromWrite != gEepromWrite) {
    lastEepromRead = gEepromRead;
    lastEepromWrite = gEepromWrite;
    gRedrawScreen = true;
    TaskAdd("EEPROM RW-", eepromRWReset, 1000, false);
  }
}

void STATUSLINE_render() {
  UI_ClearStatus();
  if (showBattery) {
    UI_Battery(gBatteryDisplayLevel);
  }

  if (gEepromRead) {
    PrintSmallEx(LCD_WIDTH - 1 - 4, 5, POS_R, C_FILL, "R");
  }

  if (gEepromWrite) {
    PrintSmallEx(LCD_WIDTH - 1, 5, POS_R, C_FILL, "W");
  }
}
