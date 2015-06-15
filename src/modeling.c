#include <pebble.h>
#include "modeling.h"

static char *zones;

void init(){
  ResHandle handle_zones = resource_get_handle(RESOURCE_ID_ZONES_FR);
  ResHandle handle_on = resource_get_handle(RESOURCE_ID_ON_FR);
  size_t handle_zones_size = resource_size(handle_zones);
  zones = (char*)malloc(handle_zones_size);
  resource_load(handle_zones, (uint8_t*)zones, handle_zones_size);
}
  
clockState time2clockState(struct tm *tick_time, language lng){
  
  init();
  char row_size = zones[0];
  char col_size = zones[1];
  
  //init matrix
  int n = 1;
  bool** state = (bool**) malloc(n * sizeof(bool));
  for (int i = 0; i < n; i++)
        state[i] = (bool*) malloc(n * sizeof(bool));
  
  //create structure
  clockState result = {state, row_size, col_size, tick_time};
  return result;
}
