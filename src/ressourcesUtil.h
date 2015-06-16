#pragma once
#include <pebble.h>
  
typedef struct {
  char* data;
  int rowNb;
  int colNb;
} MatrixData;
  
uint32_t get_id_from_locale(const char* lng); 
void destroy_Matrix_Data(MatrixData* matrix_data);
MatrixData* create_matrix_data(const char* lng);