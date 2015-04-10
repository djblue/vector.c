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

Create a homogeneous vector elements of `unit` size.

- unit: size in bytes of a single element in the vector.
  Every element in the vector must be unit bytes.

```c
vector *v = vector_create(sizeof(int));
```

## vector_create_with_capacity(unit, capacity)

Create a new vector with the indicated capacity.

- unit: size in bytes of a single element in the vector.
- capacity: initial capacity of vector.

```c
// v = [0,0,0,0,0]
vector *v = vector_create(sizeof(int), 5);
```

NOTE: the default capacity is set in `vector.h` and is
arbitrarily set to 64. Also, as the vector grows and needs
more space, it does so at a default rate of 1.5.

## vector_free(v)

Free a previously allocated vector.

- v: vector context for function.

```c
vector *v = vector_create(sizeof(int));

// use vector and of its glorious methods

vector_free(v);
```

## vector_push(v, elem)

Push an element to the back of a vector. Pass a
pointer to the element you want copied into the
vector.

- v: vector context for function.
- elem: pointer to element to copy into array. It is
  assumed the elem is of size unit used to initialize
  the vector.

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

Pop last element from vector. This just returns the address
of the last element in the vector. If you want a permanent
copy, make sure you make one.

- v: vector context for function.

```c
vector *v = vec();  // v = [0,1,2,3,4]
vector_pop(v);      // v = [0,1,2,3]
vector_pop(v);      // v = [0,1,2]
```

## vector_get(v, i)

Get the ith address from the vector.

- v: vector context for function.
- i: index of element to get. NULL will be returned if
  i is out of bounds.

```c
vector *v = vec();
vector_get(v, 0);         // 0
vector_get(v, v->length); // 4
```

## vector_splice(v, i, n)

Splice out the ith + n elements from a vector.

- v: vector context for function.
- i: the starting index to splice from.
- n: how many element to splice out.

```c
vector *v = vec();      // v = [0,1,2,3,4]
vector_splice(v, 0, 2); // v = [2,3,4]
```

## vector_slice(v, i, n)

Similar to splice, except for the elements aren't
deleted from the original vector, but rather returned
as a new vector. Remember to free it when done.

- v: vector context for function.
- i: the starting index to slice from.
- n: how many element to slice.

```c
vector *v = vec();          // v = [0,1,2,3,4]
s = vector_splice(v, 0, 2); // s = [0,1]
v;                          // v = [0,1,2,3,4]
```

## vector_each(v, func(i, item))

Apply a function to each element in a vector.

- v: vector context for function.
- func: function to call on each item.

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

Return a new vector of element that have been filtered
from the original vector. The function accepts an item
and returns 1 or 0 for true or false to determine if the
item is to be in the new vector.

- v: vector context for function.
- func: filter function.

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

## vector_map(v, unit, item func(item))

Map over a vector to produce a new vector. The returned
items don't have to be the same size as the original items.

- v: vector context for function.
- unit: unit of new items, used to initialize new vector.
- func: function which accepts old items and return new items.

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

