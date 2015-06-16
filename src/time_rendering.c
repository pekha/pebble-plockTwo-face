#include <pebble.h>
#include "time_rendering.h"
#include "ressourcesUtil.h"
  
static TextLayer *s_time_layer;  
  
void init_graphical_rendering(Window *window, const char* lng){
  
  //MatrixData* matrix_data = create_matrix_data(lng);
  //char[matrix_data->rowNb][matrix_data->colNb] = matrix_data->data

  // Create time TextLayer
  s_time_layer = text_layer_create(GRect(0, 0, 144, 164));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_text(s_time_layer,  "00:00 ln");

  // Improve the layout to be more like a watchface
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentLeft);

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
  MatrixData* matrix = create_matrix_data(lng);
  static char s[] = "           \n           \n           \n           \n           \n           \n           \n           \n           \n           \n";
  
  for (int i = 0; i < state.rowNb; i++){
    for (int j = 0; j < state.colNb; j++){
      if (state.state[i][j]){
        s[i*(state.colNb+1) + j]= matrix->data[i*state.colNb + j];
      }
      else{
        s[i*(state.colNb+1) + j]=' ';
      }
    }
  }
  destroy_Matrix_Data(matrix);
  // Create a long-lived buffer
  //static char buffer[] = "beer o'clocOooooo\nouaneeuarrunok";

  // Write the current hours and minutes into the buffer
  //if(clock_is_24h_style() == true) {
    

  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, s);
}