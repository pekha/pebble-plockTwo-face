#include <pebble.h>
#include "time_rendering.h"
#include "ressourcesUtil.h"
  
static TextLayer *s_time_layer;  
  
void init_graphical_rendering(Window *window, const char* lng){
  
  MatrixData* matrix_data = create_matrix_data(lng);
  //char[matrix_data->rowNb][matrix_data->colNb] = matrix_data->data
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%d", matrix_data->rowNb);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%d", matrix_data->colNb);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", matrix_data->data);
  for(int i = 0; i <matrix_data->rowNb * matrix_data->colNb ; i++){
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%d %c",i , matrix_data->data[i]);
  }

  // Create time TextLayer
  s_time_layer = text_layer_create(GRect(0, 55, 144, 50));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_text(s_time_layer, "00:00 ln");

  // Improve the layout to be more like a watchface
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
}

static TextLayer* create_text_layer(GRect rect, GFont font){
  TextLayer *part_layer = text_layer_create(rect);
  text_layer_set_background_color(part_layer, GColorClear);
  text_layer_set_text_color(part_layer, GColorWhite);
  text_layer_set_text(part_layer, "00");
  text_layer_set_font(part_layer, font);
  text_layer_set_text_alignment(part_layer, GTextAlignmentLeft);
  return part_layer;
}

void deinit_graphical_rendering(){
  text_layer_destroy(s_time_layer);
}

void time_rendering(clockState state, const char* lng){
  // Create a long-lived buffer
  static char buffer[] = "00:00";

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    //Use 2h hour format
    strftime(buffer, sizeof("00:00"), "%H:%M", state.tick_time);
  } else {
    //Use 12 hour format
    strftime(buffer, sizeof("00:00"), "%I:%M", state.tick_time);
  }

  strcat(buffer, lng);
  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, buffer);
}