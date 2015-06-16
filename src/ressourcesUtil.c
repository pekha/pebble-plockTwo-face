#include <pebble.h>
#include "ressourcesUtil.h"

MatrixData* create_matrix_data(const char* lng) {
  MatrixData* matrix_data = malloc(sizeof(MatrixData));
  
  // Get resource and size
  ResHandle handle = resource_get_handle(get_id_from_locale(lng));
  
  //resource size
  size_t res_size = resource_size(handle);

  // Copy to buffer
  char* row = (char*)malloc(sizeof("00"));
  char* col = (char*)malloc(sizeof("00"));
  resource_load_byte_range(handle, 0, (uint8_t*) row, 2);
  resource_load_byte_range(handle, 4, (uint8_t*) col, 2);
  matrix_data->rowNb = atoi(row);
  matrix_data->colNb = atoi(col);
  size_t data_size = matrix_data->rowNb * matrix_data->colNb * sizeof(char);
  char* data = (char*)malloc(data_size);
  resource_load_byte_range(handle, 8, (uint8_t*) data, data_size);
  matrix_data->data = data;
  return matrix_data;
}

void destroy_Matrix_Data(MatrixData* matrix_data){
  free(matrix_data->data);
  free(matrix_data);
}

uint32_t get_id_from_locale(const char* lng) {
  int res = strcmp(lng, "fr_FR");
  if( res == 0){
    return RESOURCE_ID_FILE_CLOCK_MATRIX_FR;
  }
  else{
    return RESOURCE_ID_FILE_CLOCK_MATRIX_EN;
  }
}


