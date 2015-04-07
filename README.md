# vector.c

[![Build Status](https://travis-ci.org/djblue/vector.c.svg)](https://travis-ci.org/djblue/vector.c)

Basic c vector class. Has a similar api to arrays in javascript.

# building

To build the project, do:

    make

# tests

To run all the tests, do:

    make test

# methods

Below are all the supported methods of the vector.

## vector_create(unit)

```c
vector *v = vector_create(sizeof(int));
```

## vector_free(v)

```c
vector *v = vector_create(sizeof(int));

// use vector

vector_free(v);
```

## vector_push(v, elem)

```c
vector *vec () {
  vector *v = vector_create_t(int);
  for (int i = 0; i < 5; i++) {
    vector_push(v, &i);
  }
  return v;
}
```

## vector_pop(v)

```c
vector *v = vec();  // v = [0,1,2,3,4]
vector_pop(v);      // v = [0,1,2,3]
vector_pop(v);      // v = [0,1,2]
```

## vector_get(v, i)

```c
vector *v = vec();
vector_get(v, 0);         // 0
vector_get(v, v->length); // 4
```

## vector_splice(v, i, n)

```c
vector *v = vec();      // v = [0,1,2,3,4]
vector_splice(v, 0, 2); // v = [2,3,4]
```

## vector_slice(v, i, n)

```c
vector *v = vec();          // v = [0,1,2,3,4]
s = vector_splice(v, 0, 2); // s = [0,1]
v;                          // v = [0,1,2,3,4]
```

## vector_each(v, func(i, item))

```c
vector *v = vec();
void print (int i, void *val) {
  int item = *((*int)val);
  printf("i = %d val = %d\n", i, item);
}
vector_each(v, print);
// i = 0, val = 0
// i = 1, val = 1
// i = 2, val = 2
// i = 3, val = 3
// i = 4, val = 4
```

## vector_filter(v, int func (item))

```c
vector *v = vec(), *f;

int is_even (void *val) {
  int *i = (int*) val;
  if (*i % 2 == 0) {
    return 1;
  } else {
    return 0;
  }
}

f = vector_filter(v, is_even); // f = [0,2,4]
```

## vector_map(v, int unit, item func(item))

```c
vector *v = vec(), *m;

void *square (void *val) {
  // NOTE: any items that are returned must by
  // dynamically allocated; the caller function
  // will free.
  int *i = malloc(4), j = *((int*) val);
  *i =  j * j;
  return i;
}

m = vector_map(v, square); // m = [0,1,4,9,16]
```

# macros

Below are some helper macros to help clean up your code. They mostly take
care of casting.

## vector_create_t(type)

```c
vector *v = vector_create_t(int);
```

## vector_push_t(type,v,l)

```c
vector *v = vector_create_t(int);
vector_push_t(int, v, 5);
```

## vector_pop_t(type,v)

```c
vector *v = vec();
int last = vector_pop_t(int, v);
```

## vector_get_t(type,v,i)

```c
vector *v = vec();
int last = vector_get_t(int, v, v->length); // 4
```

## vector_map_t(type,v,func)

```c
vector_map_t(int, v, func);
```

