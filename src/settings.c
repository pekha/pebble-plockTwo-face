#include <pebble.h>
#include "settings.h"
  
#define DEFAULT_BACKGROUND_VALUE GColorDarkCandyAppleRed.argb
#define DEFAULT_LETTER_ON_VALUE GColorWhite.argb
#define DEFAULT_LETTER_OFF_VALUE GColorBulgarianRose.argb
#define DEFAULT_THINER_OFF_FONT_VALUE false

static Settings* settings;
  


Settings* get_settings(){
  return settings;
}

static void load_settings(){
  uint32_t version = persist_read_int(STORAGE_VERSION_KEY); // defaults to 0 if key is missing.
  GColor8 background = (GColor8){ 
    .argb = (persist_exists(BACKGROUND_KEY) ? persist_read_int(BACKGROUND_KEY) : DEFAULT_BACKGROUND_VALUE )
  };
  GColor8 letter_on = (GColor8){
    .argb = (persist_exists(LETTER_ON_KEY) ? persist_read_int(LETTER_ON_KEY) : DEFAULT_LETTER_ON_VALUE)
  };
  GColor8 letter_off = (GColor8){
    .argb = (persist_exists(LETTER_OFF_KEY) ? persist_read_int(LETTER_OFF_KEY) : DEFAULT_LETTER_OFF_VALUE)
  };
 
  settings->background = background;
  settings->letter_on = letter_on;
  settings->letter_off = letter_off;
  settings->thiner_off_font = (persist_exists(THINER_OFF_FONT_KEY) ? persist_read_bool(THINER_OFF_FONT_KEY) : DEFAULT_THINER_OFF_FONT_VALUE);
}

/*
  GColor background;
  GColor letter_on;
  GColor letter_off;
  bool thiner_off_font;
*/
static void save_settings(){
  persist_write_int(STORAGE_VERSION_KEY, 0);
  persist_write_int(BACKGROUND_KEY, settings->background.argb);
  persist_write_int(LETTER_ON_KEY, settings->letter_on.argb);
  persist_write_int(LETTER_OFF_KEY, settings->letter_off.argb);
  persist_write_bool(THINER_OFF_FONT_KEY, settings->thiner_off_font);
}

void init_settings(){
  settings = (Settings*) malloc(sizeof(Settings));
  load_settings();
}
void deinit_settings(){
  save_settings();
  free(settings);
}
