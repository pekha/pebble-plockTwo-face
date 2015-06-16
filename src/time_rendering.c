#include <pebble.h>
#include "ressourcesUtil.h"
#include "time_rendering.h"

static TextLayer ***s_time_layer;  
static char*** letter_buffer;
static TextLayer *s_min_layer[4];
static int nbCol;
static int nbRow;
static GFont s_custom_font;
  
void init_graphical_rendering(Window *window, const char* lng){
  MatrixData* matrix_data = create_matrix_data(lng);
  nbCol = matrix_data->colNb;
  nbRow = matrix_data->rowNb;
  s_custom_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DIN_BOLD_14));
  s_time_layer = malloc(nbRow * sizeof(TextLayer**));
  letter_buffer = malloc(nbRow * sizeof(char**));
  for(int curRow = 0; curRow < nbRow; curRow ++){
    s_time_layer[curRow] = malloc(nbCol * sizeof(TextLayer*));
    letter_buffer[curRow] = malloc(nbCol * sizeof(char*));
    for(int curCol = 0; curCol < nbCol; curCol ++){
      letter_buffer[curRow][curCol] = malloc(sizeof(char)*2);
      letter_buffer[curRow][curCol][0] = matrix_data->data[coord2index(curRow, curCol)];
      letter_buffer[curRow][curCol][1] ='\0'; 
      s_time_layer[curRow][curCol] = create_text_layer(GRect(curCol*12 + curCol + 1, curRow*13 + curRow + 1, 12, 16), s_custom_font ,letter_buffer[curRow][curCol]);
      layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer[curRow][curCol]));
    }
  }
  char* round = "•";
  //round[0] = (char)149;
  
  s_min_layer[0] = create_text_layer(GRect(48,145, 12, 16), fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD), round);
  s_min_layer[1] = create_text_layer(GRect(60,145, 12, 16), fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD), round);
  s_min_layer[2] = create_text_layer(GRect(72,145, 12, 16), fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD), round);
  s_min_layer[3] = create_text_layer(GRect(84,145, 12, 16), fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD), round);
  
  for(int i = 0; i < 4; i ++){
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_min_layer[i]));
  }
  
  //dont forget destroy matrix data
  destroy_Matrix_Data(matrix_data);
  
  //set window background color
  window_set_background_color(window, GColorDarkCandyAppleRed);
}

static TextLayer* create_text_layer(GRect rect, GFont font, char* val){
  TextLayer *part_layer = text_layer_create(rect);
  text_layer_set_background_color(part_layer, GColorClear);
  text_layer_set_text_color(part_layer, GColorBulgarianRose);
  text_layer_set_font(part_layer, font);
  text_layer_set_text_alignment(part_layer, GTextAlignmentCenter);
  text_layer_set_text(part_layer, val);
  return part_layer;
}

static int coord2index(int row, int col){
  return row * nbCol + col;
}

void deinit_graphical_rendering(){
  for(int i = 0; i < nbRow; i ++){
    for(int j = 0; j < nbCol; j ++){
      text_layer_destroy(s_time_layer[i][j]);
      free(letter_buffer[i][j]);
    }
    free(s_time_layer[i]);
    free(letter_buffer[i]);
  }
  free(s_time_layer);
  free(letter_buffer);
  for(int i = 0; i < 4; i ++){
    text_layer_destroy(s_min_layer[i]);
  }
  fonts_unload_custom_font(s_custom_font);
}

void time_rendering(clockState* state, const char* lng){
   for(int curRow = 0; curRow < nbRow; curRow ++){
    for(int curCol = 0; curCol < nbCol; curCol ++){
       if(state->state[curRow][curCol]){
         text_layer_set_text_color(s_time_layer[curRow][curCol], GColorWhite);
       }
       else{
        text_layer_set_text_color(s_time_layer[curRow][curCol], GColorBulgarianRose);
       }
     }
   }
   
  int min = state->tick_time->tm_min;
  
  computeMinutes(0, min, 1);
  computeMinutes(1, min, 2);
  computeMinutes(2, min, 3);
  computeMinutes(3, min, 4);
}

static void computeMinutes(short index,int minutes, short threshold){
  text_layer_set_text_color(s_min_layer[index], minutes % 5 >= threshold ? GColorWhite : GColorBulgarianRose);
}
