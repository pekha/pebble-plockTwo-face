#pragma once

#define STORAGE_VERSION_KEY 0
#define BACKGROUND_KEY 1
#define LETTER_ON_KEY 2
#define LETTER_OFF_KEY 3
#define THINER_OFF_FONT_KEY 4
#define COMMAND_KEY 5

typedef struct {
  GColor8 background;
  GColor8 letter_on;
  GColor8 letter_off;
  bool thiner_off_font;
} Settings;

void init_settings();
void deinit_settings();
Settings* get_settings();