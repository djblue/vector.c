#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_INITIAL_CAPACITY 64
#define VECTOR_GROWTH_RATE 1.5

typedef struct {
  void *data;   // pointer to data of vector
  int unit;     // unit size of any element in vector
  unsigned long length;   // how many element are currently stored
  unsigned long capacity; // how many spaces of unit size are available
} vector;

// create a new vector
#define vector_create_t(type) (vector_create(sizeof(type)))
vector *vector_create(int unit);
// free vector resources
void vector_free(vector *v);

// push values that you can't address
#define vector_push_t(type,v,l) { type __v = l; vector_push(v,&__v); }
// push to back of vector 
void vector_push(vector *v, void *elem);
// pop last element
#define vector_pop_t(type,v) (*(type*)vector_pop(v))
void *vector_pop(vector *v);
// get element i, returns null if out of bounds
#define vector_get_t(type,v,i) (*(type*)vector_get(v,i))
void *vector_get(vector *v, int i);
// splice out n elements from index i
void vector_splice(vector *v, int i, int n);

// return new sub vector of original vector
vector *vector_slice(vector *v, int i, int n);

// apply a function to each element in array
void vector_each(vector *v, void func (int, void *));

// get a new vector filtered from v
vector *vector_filter(vector *v, int func (void *));
// get a new vector mapped from v
#define vector_map_t(type,v,func) (vector_map(v,sizeof(type),func))
vector *vector_map(vector *v, int unit, void *func (void *));

#endif
