#include <pebble.h>
#include "modeling.h"

static char *zones;
static char *on;
static size_t handle_zones_size;
static size_t handle_on_size;
void init(language lng){
  ResHandle handle_zones = resource_get_handle(RESOURCE_ID_FILE_CLOCK_ZONES_FR);
  ResHandle handle_on = resource_get_handle(RESOURCE_ID_FILE_CLOCK_ON_FR);
  handle_zones_size = resource_size(handle_zones);
  handle_on_size = resource_size(handle_on);
  zones = (char*)malloc(handle_zones_size);
  on = (char*)malloc(handle_on_size);
  resource_load(handle_zones, (uint8_t*)zones, handle_zones_size);
  resource_load(handle_on, (uint8_t*)on, handle_on_size);
}

void destroy(){
  free(on);
  free(zones);
}
  
clockState time2clockState(struct tm *tick_time, language lng){
  init(lng);

  char row_size = zones[0];
  char col_size = zones[1];
  int on_index = tick_time->tm_hour * 60 + tick_time->tm_min;
  uint32_t ons = (on[on_index] << 16) + (on[on_index + 1] << 8) + on[on_index];
  
  bool** state = (bool**) malloc(row_size * sizeof(bool*));
  for (int i = 0; i < row_size; i++)
        state[i] = (bool*) malloc(col_size * sizeof(bool));

  
  //init matrix
  for (int i = 0; i < row_size; i++){
    for (int j = 0; j < col_size; j++){
      uint32_t is_on = 1;
      is_on = is_on << zones[i*col_size + j];
      state[i][j] = ons & is_on;
    }
  }
  
  //create structure
  clockState result = {state, row_size, col_size, tick_time};

  destroy();
  
  return result;
}