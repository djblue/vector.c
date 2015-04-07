#include <stdio.h>
#include <stdlib.h>

#include "test.h"
#include "vector.h"

vector *vec () {
  vector *v = vector_create_t(int);
  for (int i = 0; i < 10; i++) {
    vector_push(v, &i);
  }
  return v;
}

void my_print_vector (void *val) {
  int *i = (int*) val;
  printf("%d ", *i);
}

void *square (void *val) {
  int *i = malloc(4), j = *((int*) val);
  *i =  j * j;
  return i;
}

int is_even (void *val) {
  int *i = (int*) val;
  if (*i % 2 == 0) {
    return 1;
  } else {
    return 0;
  }
}

int is_odd (void *v) {
  return !is_even(v);
}

int main (int argc, char *argv[]) {

  begin("vector#create()");
    vector *v = vector_create(4);
    assert(v->length == 0, "vector has correct length");
    assert(v->capacity == 64, "vector has correct capacity");
    assert(v->unit == 4, "vector has correct units");
    vector_free(v);
  end();

  begin("vector#get()");
    vector *v = vec();
    for (int i = 0; i < v->length; i++) {
      assert(vector_get_t(int, v, i) == i, "get correct value");
    }
    vector_free(v);
  end();

  begin("vector#push()");
    vector *v = vector_create(4);
    for (int i = 0; i < 10; i++) {
      vector_push(v, &i);
      assert(v->length == i+1, "vector correct length");
    }
    vector_free(v);
  end();

  begin("vector#pop()");
    vector *v = vec();
    for (int i = 9; i >= 0; i--) {
      assert(vector_pop_t(int, v) == i, "pops last element");
      assert(v->length == i, "correct length");
    }
    vector_free(v);
  end();

  begin("vector#splice()");
    vector *v = vec();
    vector_splice(v, 0, 5);
    assert(v->length == 5, "splice correctly");
    for (int i = 0; i < 5; i++) {
      assert(vector_get_t(int, v, i) == i+5, "splice correctly");
    }
    vector_splice(v, 0, 5);
    assert(v->length == 0, "splice correctly");
    vector_free(v);
  end();

  begin("vector#slice()");
    vector *v = vec(), *s;

    s = vector_slice(v, 0, 1);
    assert(s->length == 1, "correctly sliced");
    assert(vector_get_t(int, s, 0) == 0, "correctly sliced");
    vector_free(s);

    s = vector_slice(v, 1, 1);
    assert(s->length == 1, "correctly sliced");
    assert(vector_get_t(int, s, 0) == 1, "correctly sliced");
    vector_free(s);

    s = vector_slice(v, 7, 2);
    assert(s->length == 2, "correctly sliced");
    assert(vector_get_t(int, s, 0) == 7, "correctly sliced");
    assert(vector_get_t(int, s, 1) == 8, "correctly sliced");
    vector_free(s);

    vector_free(v);
  end();

  begin("vector#each()");
    vector *v = vec();
    void test (int i, void *val) {
      int j = *((int*)val);
      assert(j == vector_get_t(int, v, i), "correct value");
    }
    vector_each(v, test);
    vector_free(v);
  end();

  begin("vector#filter()");
    vector *v = vec(), *f;
    f = vector_filter(v, is_even);
    assert(f->length == 5, "filter works correctly");
    vector_free(f);
    f = vector_filter(v, is_odd);
    assert(f->length == 5, "filter works correctly");
    vector_free(f);
    vector_free(v);
  end();

  begin("vector#map()");
    vector *v = vec(), *m;
    m = vector_map_t(int, v, square);
    assert(m->length == v->length, "correctly maps length");
    for (int i = 0; i < m->length; i++) {
      assert(vector_get_t(int, m, i) == i*i, "correctly maps square function");
    }
    vector_free(m);
    vector_free(v);
  end();

  return 0;
}
