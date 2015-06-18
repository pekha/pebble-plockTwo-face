#pragma once
  
typedef struct {
  GColor background;
  GColor letter_on;
  GColor letter_off;
  bool thiner_off_font;
} Settings;

void init();
void deinit();
Settings get();
void save(Settings);