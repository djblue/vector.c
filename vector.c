#include <stdlib.h>
#include <string.h>

#include "vector.h"

typedef char byte_t;

static vector *vector_create_real(size_t unit, unsigned long *cap) {
  vector *v = (vector*) malloc(sizeof(vector));

  if (v == NULL) return NULL;

  v->capacity = cap ? *cap : VECTOR_INITIAL_CAPACITY;
  if (v->capacity < VECTOR_INITIAL_CAPACITY) {
    v->capacity = VECTOR_INITIAL_CAPACITY;
  }
  v->unit = unit;
  v->length = 0;

  v->data = calloc(v->capacity, v->unit);

  if (v->data == NULL) {
    free(v);
    return NULL;
  }

  return v;
}

vector *vector_create(size_t unit) {
  return vector_create_real(unit, NULL);
}

vector *vector_create_with_capacity(size_t unit, unsigned long cap) {
  return vector_create_real(unit, &cap);
}

void vector_free(vector* v) {
  free(v->data);
  free(v);
}

void vector_resize (vector *v) {
  v->capacity = (int)(v->capacity * VECTOR_GROWTH_RATE);
  v->data = realloc(v->data, v->unit * v->capacity);
}

void vector_push(vector *v, void *elem) {
  if (v->length == v->capacity) {
    vector_resize(v);
  }

  // copy over element
  memcpy((byte_t*)v->data + (v->unit * v->length), elem, v->unit);

  v->length++; // increase length of vector
}

void *vector_pop(vector* v) {

  // no elements left to pop
  if (v->length == 0) return NULL;

  // change length of vector
  v->length--;

  // return address of last element
  return (byte_t*)v->data + (v->unit * v->length);
}

void *vector_get(vector *v, int i) {
  // i is out of range
  if  (i < 0 || i >= v->length) return NULL;

  return (byte_t*)v->data + (i * v->unit);
}

void vector_splice(vector *v, int i, int n) {
  int max;
  byte_t *start = (byte_t*)v->data + (v->unit * i);

  // n should not exceed max
  max = v->length - i;
  if (n > max) n = max;

  memmove(start, start + (n * v->unit), v->unit * (v->length - n));

  v->length -= n; // remove n elements
}

vector *vector_slice (vector *v, int i, int n) {
  vector *s = vector_create_with_capacity(v->unit, n);
  memcpy(s->data, (byte_t*)v->data + (i * v->unit), n*v->unit);
  s->length = n;
  return s;
}

void vector_each(vector *v, void func (int, void *)) {
  int i;
  byte_t *p;
  for (i = 0; i < v->length; i++) {
    p = (byte_t*)v->data + (i * v->unit);
    func(i, p);
  }
}

vector *vector_filter(vector *v, int func (void *)) {

  int i, res;

  // no *_with_capacity because we have no idea how big the resulting
  // vector could end up.
  vector *filter = vector_create(v->unit);

  for (i = 0; i < v->length; i++) {
    res = func((byte_t*)v->data + (i * v->unit));
    if (res == 1) {
      vector_push(filter, (byte_t*)v->data + (i * v->unit));
    }
  }

  return filter;
}

vector *vector_map(vector *v, size_t unit, void *func (void *)) {

  int i;
  void *res;

  vector *map = vector_create_with_capacity(unit, v->capacity);

  for (i = 0; i < v->length; i++) {
    res = func((byte_t*)v->data + (i * v->unit));
    vector_push(map, res);
    free(res);
  }

  return map;
}
