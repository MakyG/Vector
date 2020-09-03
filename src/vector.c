/**
 * @file       vector.c
 * @author     Tomáš Makyča
 * @date       15.3.2020
 * @brief      Implementation of vector.h header file
 * ******************************************
 * @par       COPYRIGHT NOTICE (c) 2019 TBU in Zlin. All rights reserved.
 */

#include "vector.h"
#include "mymalloc.h"

Vector_t *Vector_Create(uint64_t initial_size, uint32_t alloc_step) {
  Vector_t *vector = myMalloc(sizeof (Vector_t));
  if(vector == NULL){
      return NULL;
  }

  vector->items = myMalloc(initial_size * sizeof (uint64_t));
  if(vector->items == NULL){
      myFree(vector);
      return NULL;
  }

  vector->size = initial_size;
  vector->free_cells = initial_size;
  vector->alloc_step = alloc_step;

  return vector;
}

Vector_t *Vector_Copy(const Vector_t *const original) {

    if (original == NULL){
        return NULL;
    }

    Vector_t* new_vector = Vector_Create(original->size, original->alloc_step);

    if (new_vector == NULL){
        return NULL;
    }

    for (unsigned int i = 0; i < Vector_Length(original); i++){
        new_vector->items[i] = original->items[i];
    }
    new_vector->free_cells = original->free_cells;
  return new_vector;
}

void Vector_Clear(Vector_t *const vector) {
  if(vector == NULL) {
      return;
  }
  myFree(vector->items);
  vector->items = NULL;
  vector->size = 0;
  vector->free_cells = 0;
}

uint64_t Vector_Length(const Vector_t *const vector) {
  if(vector == NULL){
      return UINT64_MAX;
  }
  return vector->size - vector->free_cells;
}

bool Vector_At(const Vector_t *const vector, uint64_t position, uint64_t *const value) {
  if(vector == NULL || value == NULL){
      return false;
  }
  if(position < Vector_Length(vector)){
      *value = vector->items[position];
      return true;
  }
  return false;
}

bool Vector_Remove(Vector_t *const vector, uint64_t position) {
    if(vector == NULL){
        return false;
    }

    if(position >= Vector_Length(vector)){
        return false;
    }

    for(uint64_t i = position; i < Vector_Length(vector); i++){
        vector->items[i] = vector->items[i + 1];
    }
    vector->free_cells++;

  return true;
}

void Vector_Append(Vector_t *const vector, uint64_t value) {
  if(vector == NULL){
      return;
  }

  if(vector->free_cells == 0){
      uint64_t *p = myRealloc(vector->items, (vector->size + vector->alloc_step) * sizeof (uint64_t));

      if(p == NULL){
          return;
      }
      vector->items = p;
      vector->size += vector->alloc_step;
      vector->free_cells += vector->alloc_step;
  }

  vector->items[Vector_Length(vector)] = value;
  vector->free_cells--;
}

bool Vector_Contains(const Vector_t *const vector, uint64_t value) {
    if(vector == NULL){
        return false;
    }

    for (uint64_t i = 0; i < Vector_Length(vector); i++){
        if(value == vector->items[i]){
            return true;
        }
    }
    return false;
}

uint64_t Vector_IndexOf(const Vector_t *const vector, uint64_t value, uint64_t from) {
    if(vector == NULL){
        return -1;
    }

    for (uint64_t i = from; i < Vector_Length(vector); i++){
        if(value == vector->items[i]){
            return i;
        }
    }

    return -1;
}

void Vector_Fill(const Vector_t *const vector, uint64_t value, uint64_t start_position, uint64_t end_position) {
    if(vector == NULL){
        return;
    }
    if(start_position > Vector_Length(vector)){
        return;
    }

    if(end_position < Vector_Length(vector)){
        for(uint64_t i = start_position; i <= end_position; i++){
            vector->items[i] = value;
        }
        return;
    } else{
        for(uint64_t i = start_position; i < Vector_Length(vector); i++){
             vector->items[i] = value;
        }
    }

    return;
}

void Vector_Destroy(Vector_t **const vector) {
    if (vector == NULL)
        return;

    Vector_t* ptr = *vector;
    myFree(ptr->items);
    ptr->items = NULL;
    myFree(ptr);
    *vector = NULL;
}
