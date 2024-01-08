#include "scanlists.h"
#include "../external/printf/printf.h"
#include "../helper/channels.h"
#include "../helper/measurements.h"
#include "../ui/graphics.h"
#include "../ui/menu.h"
#include "../ui/statusline.h"
#include "apps.h"
#include <stdbool.h>
#include <string.h>

static uint8_t scanlist = 255;
static uint16_t count = 0;

uint16_t channels[350] = {0};

uint16_t currentIndex = 0;

static void getChItem(uint16_t i, uint16_t index, bool isCurrent) {
  CH ch;
  const uint8_t y = MENU_Y + i * MENU_ITEM_H;
  CHANNELS_Load(index, &ch);
  if (isCurrent) {
    FillRect(0, y, LCD_WIDTH - 3, MENU_ITEM_H, C_FILL);
  }
  if (IsReadable(ch.name)) {
    PrintMediumEx(8, y + 8, POS_L, C_INVERT, "%s", ch.name);
  } else {
    PrintMediumEx(8, y + 8, POS_L, C_INVERT, "CH-%u", index + 1);
    return;
  }
  char scanlistsStr[9] = "";
  for (uint8_t i = 0; i < 8; ++i) {
    scanlistsStr[i] = ch.memoryBanks & (1 << i) ? '1' + i : '-';
  }
  PrintSmallEx(LCD_WIDTH - 1, y + 8, POS_R, C_INVERT, "%s", scanlistsStr);
}

static void getScanlistItem(uint16_t i, uint16_t index, bool isCurrent) {
  uint16_t chNum = channels[index];
  CH ch;
  const uint8_t y = MENU_Y + i * MENU_ITEM_H;
  CHANNELS_Load(chNum, &ch);
  if (isCurrent) {
    FillRect(0, y, LCD_WIDTH - 3, MENU_ITEM_H, C_FILL);
  }
  if (IsReadable(ch.name)) {
    PrintMediumEx(8, y + 8, POS_L, C_INVERT, "%s", ch.name);
  } else {
    PrintMediumEx(8, y + 8, POS_L, C_INVERT, "CH-%u", index + 1);
    return;
  }
  char scanlistsStr[9] = "";
  for (uint8_t i = 0; i < 8; ++i) {
    scanlistsStr[i] = ch.memoryBanks & (1 << i) ? '1' + i : '-';
  }
  PrintSmallEx(LCD_WIDTH - 1, y + 8, POS_R, C_INVERT, "%s", scanlistsStr);
}

static void loadScanlist(uint8_t n) {
  uint16_t max = CHANNELS_GetCountMax();
  uint8_t scanlistMask = 1 << n;
  count = 0;
  for (uint16_t i = 0; i < max; ++i) {
    if ((CHANNELS_Scanlists(i) & scanlistMask) == scanlistMask) {
      channels[count] = i;
      count++;
    }
  }
}

static void toggleScanlist(uint8_t n) {
  CH ch;
  CHANNELS_Load(currentIndex, &ch);
  ch.memoryBanks ^= 1 << n;
  CHANNELS_Save(currentIndex, &ch);
}

void SCANLISTS_init() {
  currentIndex = 0;
  gRedrawScreen = true;
  count = CHANNELS_GetCountMax();
}

void SCANLISTS_update() {}

static bool repeatHeld = false;

bool SCANLISTS_key(KEY_Code_t key, bool bKeyPressed, bool bKeyHeld) {
  if (!bKeyPressed) {
    repeatHeld = false;
  }
  if (bKeyPressed || (!bKeyPressed && !bKeyHeld)) {
    switch (key) {
    case KEY_UP:
      IncDec16(&currentIndex, 0, count, -1);
      return true;
    case KEY_DOWN:
      IncDec16(&currentIndex, 0, count, 1);
      return true;
    default:
      break;
    }
  }
  if (bKeyHeld && bKeyPressed && !repeatHeld) {
    repeatHeld = true;
    switch (key) {
    case KEY_1:
    case KEY_2:
    case KEY_3:
    case KEY_4:
    case KEY_5:
    case KEY_6:
    case KEY_7:
    case KEY_8:
      scanlist = key - KEY_1;
      loadScanlist(scanlist);
      currentIndex = 0;
      return true;
    case KEY_0:
      scanlist = 255;
      currentIndex = 0;
      count = CHANNELS_GetCountMax();
      return true;
    case KEY_UP:
      IncDec16(&currentIndex, 0, count, -1);
      return true;
    case KEY_DOWN:
      IncDec16(&currentIndex, 0, count, 1);
      return true;
    default:
      break;
    }
  }
  if (!bKeyPressed && !bKeyHeld) {
    switch (key) {
    case KEY_1:
    case KEY_2:
    case KEY_3:
    case KEY_4:
    case KEY_5:
    case KEY_6:
    case KEY_7:
    case KEY_8:
      toggleScanlist(key - KEY_1);
      return true;
    case KEY_EXIT:
      APPS_exit();
      return true;
    default:
      return false;
    }
  }

  return false;
}

void SCANLISTS_render() {
  UI_ClearScreen();
  if (scanlist == 255) {
    STATUSLINE_SetText("CH scanlists");
    UI_ShowMenuEx(getChItem, count, currentIndex, MENU_LINES_TO_SHOW + 1);
  } else {
    STATUSLINE_SetText("CH scanlist #%u", scanlist + 1);
    UI_ShowMenuEx(getScanlistItem, count, currentIndex, MENU_LINES_TO_SHOW + 1);
  }
}
