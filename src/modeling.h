#pragma once
#include <pebble.h>

typedef struct {
  bool ** state;
  int rowNb;
  int colNb;
  struct tm *tick_time;
} clockState;
  
clockState time2clockState(struct tm *tick_time, const char* lng);