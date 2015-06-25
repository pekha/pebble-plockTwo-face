#include <pebble.h>
#include "main.h"
#include "modeling.h"
#include "time_rendering.h"
#include "settings.h"
  
static Window *s_main_window;
static char* current_lng;
void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  //convert time to matrix state
  clockState state = time2clockState(tick_time);
  
  // render state
  time_rendering(&state, current_lng);
}

static void main_window_load(Window *window) {
  // init graphical rendering
  init_graphical_rendering(window, current_lng);
  
  // Make sure the time is displayed from the start
  update_time();
}

static void main_window_unload(Window *window) {
  // deinit Graphical rendering
  deinit_graphical_rendering();
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static int32_t getColor(GColor8 color){
  int32_t result = 0;
  result += color.r * 85 * 0x100;
  result += color.g * 85 * 0x10;
  result += color.b * 85 * 0x1;
  return result;
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message received!");
  
  Settings* settings = get_settings();
  Tuple *command = dict_find(iterator, COMMAND_KEY);
  if (command != NULL){
    if (strcmp(command->value->cstring, "GET_SETTINGS") == 0){
      DictionaryIterator *iter;
      app_message_outbox_begin(&iter);
      dict_write_int32(iter, BACKGROUND_KEY, getColor(settings->background));
      dict_write_int32(iter, LETTER_ON_KEY, getColor(settings->letter_on));
      dict_write_int32(iter, LETTER_OFF_KEY, getColor(settings->letter_off));
      dict_write_uint8(iter, THINER_OFF_FONT_KEY, settings->thiner_off_font);
      app_message_outbox_send();
    }
    else if (strcmp(command->value->cstring, "SET_SETTINGS") == 0){
      Tuple *t = dict_read_first(iterator);
      while (t != NULL) {
        // Process this pair's key
        switch (t->key) {
          case BACKGROUND_KEY:
            settings->background = GColorFromHEX((int)t->value->int32);
          break;
          case LETTER_ON_KEY:
            settings->letter_on = GColorFromHEX((int)t->value->int32);
          break;
          case LETTER_OFF_KEY:
            settings->letter_off = GColorFromHEX((int)t->value->int32);
          break;
          case THINER_OFF_FONT_KEY:
            settings->thiner_off_font = ((bool)t->value->uint8);
          break;
        }
    
        // Get next pair, if any
        t = dict_read_next(iterator);
      }
      main_window_unload(s_main_window);
      main_window_load(s_main_window);
    }
  }
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

  
static void init() {
  init_settings();

  // get current language 
  initCurrentLng();
  
  // Initialize data modeling
  init_time2clockState(current_lng);
  
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  // Register APP comunication
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  const uint32_t inbound_size = 64;
  const uint32_t outbound_size = 64;
  app_message_open(inbound_size, outbound_size);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
  destroy_time2clockState();
  deinit_settings();
}

static void initCurrentLng(){
  int size =  strlen(i18n_get_system_locale());
  current_lng = "fr_FR"; //malloc(size * sizeof(char));
  //strcpy(current_lng,i18n_get_system_locale());
  APP_LOG(APP_LOG_LEVEL_DEBUG, "locale : %s", current_lng);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
