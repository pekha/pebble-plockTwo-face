#include <pebble.h>
#include "modeling.h"

clockState time2clockState(struct tm *tick_time, language lng){
  
  //init matrix
  int n = 1;
  bool** state = (bool**) malloc(n * sizeof(bool));
  for (int i = 0; i < n; i++)
        state[i] = (bool*) malloc(n * sizeof(bool));
  
  //create structure
  clockState result = {state, 0, 0, tick_time};
  return result;
}
