#pragma once
#include <pebble.h>

typedef struct {
  bool ** state;
  int rowNb;
  int colNb;
  struct tm *tick_time;
} clockState;
  
typedef enum {LNG_FR, LNG_EN} language;

clockState time2clockState(struct tm *tick_time, language lng);