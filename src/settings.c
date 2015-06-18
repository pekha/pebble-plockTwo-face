#include <pebble.h>
#include "settings.h"
  
#define DEFAULT_BACKGROUND_VALUE GColorDarkCandyAppleRed.argb
#define DEFAULT_LETTER_ON_VALUE GColorWhite.argb
#define DEFAULT_LETTER_OFF_VALUE GColorBulgarianRose.argb
#define DEFAULT_THINER_OFF_FONT_VALUE false

#define STORAGE_VERSION_KEY 0
#define BACKGROUND_KEY 1
#define LETTER_ON_KEY 2
#define LETTER_OFF_KEY 3
#define THINER_OFF_FONT_KEY 4

void init_settings(){
  
}
void deinit_settings(){
  
}

Settings get_settings(){
  uint32_t version = persist_read_int(STORAGE_VERSION_KEY); // defaults to 0 if key is missing.
  GColor8 background = (GColor8){ 
    .argb = (uint8_t)(persist_exists(BACKGROUND_KEY) ? persist_read_int(BACKGROUND_KEY) : DEFAULT_BACKGROUND_VALUE )
  };
  GColor8 letter_on = (GColor8){
    .argb = (uint8_t)(persist_exists(LETTER_ON_KEY) ? persist_read_int(LETTER_ON_KEY) : DEFAULT_LETTER_ON_VALUE)
  };
  GColor8 letter_off = (GColor8){
    .argb = (uint8_t)(persist_exists(LETTER_OFF_KEY) ? persist_read_int(LETTER_OFF_KEY) : DEFAULT_LETTER_OFF_VALUE)
  };
 
  Settings s = (Settings){
    .background = background,
    .letter_on = letter_on,
    .letter_off = letter_off,
    .thiner_off_font = (persist_exists(THINER_OFF_FONT_KEY) ? persist_read_bool(THINER_OFF_FONT_KEY) : DEFAULT_THINER_OFF_FONT_VALUE)
  };
  return s;
}

/*
  GColor background;
  GColor letter_on;
  GColor letter_off;
  bool thiner_off_font;
*/
void save_settings(Settings settings){
  persist_write_int(BACKGROUND_KEY, settings.background.argb);
  persist_write_int(LETTER_ON_KEY, settings.letter_on.argb);
  persist_write_int(LETTER_OFF_KEY, settings.letter_off.argb);
  persist_write_bool(THINER_OFF_FONT_KEY, settings.thiner_off_font);
}