#include <stdlib.h>

typedef struct {
  void *data;
  size_t capacity;
  size_t size;
  size_t data_size;
} array;

array *array_init(size_t capacity, size_t data_size);

void array_print_int(const array *arr);

int array_insert(array *arr, size_t index, void *data);
