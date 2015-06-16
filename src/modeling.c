#include <pebble.h>
#include "modeling.h"

static char *zones;
static char *on;
static size_t handle_zones_size;
static size_t handle_on_size;
static char row_size;
static char col_size;
static bool** state;

static ResHandle get_zones_res_handle(char* lng){
  ResHandle handle_zones = resource_get_handle(RESOURCE_ID_FILE_CLOCK_ZONES_EN);
  if (strcmp("fr_FR", lng) == 0){
    handle_zones = resource_get_handle(RESOURCE_ID_FILE_CLOCK_ZONES_FR);
  }
  
  return handle_zones;
}

static ResHandle get_on_res_handle(char* lng){
  ResHandle handle_on = resource_get_handle(RESOURCE_ID_FILE_CLOCK_ON_EN);
  if (strcmp("fr_FR", lng) == 0){
    handle_on = resource_get_handle(RESOURCE_ID_FILE_CLOCK_ON_FR);
  }
  return handle_on;
}

void init_time2clockState(char* lng){
  ResHandle handle_zones = get_zones_res_handle(lng);
  ResHandle handle_on = get_on_res_handle(lng);
  handle_zones_size = resource_size(handle_zones);
  handle_on_size = resource_size(handle_on);
  zones = (char*)malloc(handle_zones_size);
  on = (char*)malloc(handle_on_size);
  resource_load(handle_zones, (uint8_t*)zones, handle_zones_size);
  resource_load(handle_on, (uint8_t*)on, handle_on_size);
  
  row_size = zones[0];
  col_size = zones[1];
  
  state = (bool**) malloc(row_size * sizeof(bool*));
  for (int i = 0; i < row_size; i++){
    state[i] = (bool*) malloc(col_size * sizeof(bool));
  }
}

void destroy_time2clockState(){
  for (int i = 0; i < row_size; i++){
    free(state[i]);
  }
  free(state);
  free(on);
  free(zones);
}
  
clockState time2clockState(struct tm *tick_time){
  int on_index = (tick_time->tm_hour * 60 + tick_time->tm_min) * 4;
  uint32_t ons = (on[on_index] << 24) + (on[on_index + 1] << 16) + (on[on_index + 2] << 8) + on[on_index + 3];

  for (int i = 0; i < row_size; i++){
    for (int j = 0; j < col_size; j++){
      uint32_t is_on = 1;
      is_on = is_on << zones[2 + i*col_size + j];
      state[i][j] = ons & is_on;
    }
  }
  
  //create structure
  clockState result = {state, row_size, col_size, tick_time};
  return result;
}
