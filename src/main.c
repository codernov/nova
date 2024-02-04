#include "apps/apps.h"
#include "board.h"
#include "driver/audio.h"
#include "driver/backlight.h"
#include "driver/keyboard.h"
#include "driver/st7565.h"
#include "driver/system.h"
#include "driver/systick.h"
#include "driver/uart.h"
#include "helper/battery.h"
#include "helper/presetlist.h"
#include "radio.h"
#include "scheduler.h"
#include "settings.h"
#include "svc.h"
#include "ui/graphics.h"
#include <stdbool.h>
#include <stdint.h>

void _putchar(char c) {}

void selfTest(void) {
  PrintSmall(0, 0, "PRS O:%u SZ:%u", PRESETS_OFFSET, PRESET_SIZE);
  PrintSmall(0, 18, "SET O:%u SZ:%u", SETTINGS_OFFSET, SETTINGS_SIZE);
  ST7565_Blit();

  while (true)
    continue;
}

// TODO:

// static void TX(void) {
// DEV = 300 for SSB
// SAVE 74, dev
// }

static void AddTasks(void) {
  SVC_Toggle(SVC_KEYBOARD, true, 10);
  SVC_Toggle(SVC_LISTEN, true, 10);
  SVC_Toggle(SVC_APPS, true, 1);
  SVC_Toggle(SVC_SYS, true, 1000);
  SVC_Toggle(SVC_RENDER, true, 25);

  APPS_run(gSettings.mainApp);
}

static uint8_t introIndex = 0;
static void Intro(void) {
  char pb[] = "-\\|/";
  UI_ClearScreen();
  PrintMedium(4, 0 + 12, "OSFW");
  PrintMedium(16, 2 * 8 + 12, "reb0rn");
  PrintMedium(72, 2 * 8 + 12, "%c", pb[introIndex & 3]);
  PrintSmall(96, 46, "by fagci");
  ST7565_Blit();
  if (PRESETS_Load()) {
    if (gSettings.beep)
      AUDIO_PlayTone(1400, 50);

    RADIO_LoadCurrentVFO();
    // RADIO_SetupByCurrentVFO();

    TaskRemove(Intro);
    if (gSettings.beep)
      AUDIO_PlayTone(1400, 50);
    AddTasks();
  }
}

void Main(void) {
  SYSTICK_Init();
  SYSTEM_ConfigureSysCon();

  BOARD_Init();
  BACKLIGHT_Toggle(true);

  SETTINGS_Load();

  UART_Init();

  BATTERY_UpdateBatteryInfo();
  RADIO_SetupRegisters();

  BACKLIGHT_SetDuration(BL_TIME_VALUES[gSettings.backlight]);
  BACKLIGHT_SetBrightness(gSettings.brightness);
  BACKLIGHT_On();

  if (KEYBOARD_Poll() == KEY_EXIT) {
    APPS_run(APP_RESET);
    TaskAdd("Update", APPS_update, 1, true, 100);
  } else if (KEYBOARD_Poll() == KEY_STAR) {
    PrintMediumEx(0, 7, POS_L, C_FILL, "SET: %u %u", SETTINGS_OFFSET,
                  SETTINGS_SIZE);
    PrintMediumEx(0, 7 + 8, POS_L, C_FILL, "VFO: %u %u", VFOS_OFFSET, VFO_SIZE);
    ST7565_Blit();
  } else if (KEYBOARD_Poll() == KEY_F) {
    UART_IsLogEnabled = 5;
    TaskAdd("Intro", Intro, 2, true, 5);
  } else if (KEYBOARD_Poll() == KEY_MENU) {
    // selfTest();
    PrintMediumEx(LCD_WIDTH - 1, 7, POS_R, C_FILL, "%u", PRESETS_Size());
    for (uint8_t i = 0; i < PRESETS_Size(); ++i) {
      Preset p;
      PRESETS_LoadPreset(i, &p);
      PrintSmall(i / 10 * 40, 6 * (i % 10) + 6, "%u - %u",
                 p.band.bounds.start / 100000, p.band.bounds.end / 100000);
    }
    ST7565_Blit();
  } else {
    TaskAdd("Intro", Intro, 2, true, 5);
  }

  while (true) {
    TasksUpdate();
  }
}
