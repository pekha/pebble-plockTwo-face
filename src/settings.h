#pragma once
  
typedef struct {
  GColor8 background;
  GColor8 letter_on;
  GColor8 letter_off;
  bool thiner_off_font;
} Settings;

void init_settings();
void deinit_settings();
Settings get_settings();
void save_settings(Settings);