#include <pebble.h>
#include "main.h"
#include "modeling.h"
#include "time_rendering.h"
  
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
  
static void init() {
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
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
  destroy_time2clockState();
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
