#include <pebble.h>
#include "settings.h"
  
#define DEFAULT_BACKGROUND_VALUE GColorDarkCandyAppleRed.argb;
#define DEFAULT_LETTER_ON_VALUE GColorWhite.argb;
#define DEFAULT_LETTER_OFF_VALUE GColorBulgarianRose.argb;
#define DEFAULT_THINER_OFF_FONT_VALUE false;
  
void init(){
  
}
void deinit(){
  
}

Settings get(){
  uint32_t version = persist_read_int(STORAGE_VERSION_KEY); // defaults to 0 if key is missing.
  switch(version) {
    case 0:
    break;
  }
  Settings s;
  s.background = { persist_exists(BACKGROUND_KEY) ? persist_read_int(BACKGROUND_KEY) : DEFAULT_BACKGROUND_VALUE };
  s.letter_on = { persist_exists(LETTER_ON_KEY) ? persist_read_int(LETTER_ON_KEY) : DEFAULT_LETTER_ON_VALUE };
  s.letter_off = {persist_exists(LETTER_OFF_KEY) ? persist_read_int(LETTER_OFF_KEY) : DEFAULT_LETTER_OFF_VALUE};
  s.thiner_off_font = persist_exists(THINER_OFF_FONT_KEY) ? persist_read_bool(THINER_OFF_FONT_KEY) : DEFAULT_THINER_OFF_FONT_VALUE;
  
  return s;
}

/*
  GColor background;
  GColor letter_on;
  GColor letter_off;
  bool thiner_off_font;
*/
void save(Settings settings){
  persist_write_int(BACKGROUND_KEY, settings.background.argb);
  persist_write_int(LETTER_ON_KEY, settings.letter_on.argb);
  persist_write_int(LETTER_OFF_KEY, settings.letter_off.argb);
  persist_write_bool(THINER_OFF_FONT, settings.thiner_off_font);
}