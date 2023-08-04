#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "array.h"

array *array_init(size_t capacity, size_t data_size) {
  array *a = malloc(sizeof(array));
  if (a == NULL)
    return 0;
  a->data = malloc(capacity * data_size);
  a->data_size = data_size;
  a->capacity = capacity;
  a->size = 0;
  return a;
}

void array_print_int(const array *arr) {
  assert(arr != 0);
  assert(arr->data != 0);
  printf("data_size = '%zu', size = '%zu', length = '%zu'\n", arr->data_size,
         arr->capacity, arr->size);
  for (int k = 0; k < arr->capacity; k++) {
    printf("\tA[%d] = '%d'\n", k, *((int *)(arr->data + k * arr->data_size)));
    if (k == (arr->size - 1))
      printf("\tGargbage from here on... \n");
  }
}

int array_insert(array *arr, size_t index, void *data) {
  assert(arr != 0);
  assert(arr->data != 0);

  if (arr->size == 0) {
    memcpy(arr->data, data, arr->data_size);
    arr->size++;
    return 1;
  }

  if (data == NULL)
    return -2;

  if (index > arr->size)
    return -1;

  if (arr->size >= arr->capacity)
    return 0;

  size_t ds = arr->data_size, l = arr->size;
  void *d = arr->data + ((index + 1) * ds), *s = arr->data + (index * ds);
  memmove(d, s, (l - index) * ds);
  memcpy(s, data, ds);
  arr->size++;
  return 1;
}
