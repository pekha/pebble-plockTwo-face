#pragma once
#include "modeling.h"
  
void init_graphical_rendering(Window *window, const char* lng);

void deinit_graphical_rendering();

void time_rendering(clockState* state, const char* lng);

static TextLayer* create_text_layer(GRect rect, GFont font, char* val);

static int coord2index(int row, int col);

static void computeMinutes(short index, int minutes, short threshold);