#pragma once
#include "modeling.h"
  
void init_graphical_rendering(Window *window, const char* lng);

void deinit_graphical_rendering();

void time_rendering(clockState state, const char* lng);