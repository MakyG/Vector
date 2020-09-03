/**
 * @file    vector.h
 * @author  Roman Dosek, Tomas Jurena
 * @date    2/2015
 * @brief   Headers of Vector data structure
 */

#ifndef __VECTOR_H
#define __VECTOR_H

#include <stdbool.h>
#include <stdint.h>

/* Vector structure */
typedef struct {
  uint64_t *items;     /**< Internal pointer to allocated memory */
  uint64_t size;       /**< Number of currently allocated cells */
  uint64_t free_cells; /**< Number of unused cells inside Vector?le */
  uint32_t alloc_step; /**< Number of cells allocated during expanding */
} Vector_t;

/* Public Vector API */
/**
 * @brief   Creates a vector with initial size specified by a parameter.
 *  After return from the function the owner of a pointer to a vector
 *      structure is the user instead of the library.
 * @param[in]   initial_size    initial size of the vector
 * @param[in]   alloc_step      Defines the size of memory allocation by blocks
 * @return  New allocated vector structure or NULL in case of failure.
 */
Vector_t *Vector_Create(uint64_t initial_size, uint32_t alloc_step);

/**
 * @brief   Creates a separate copy of a vector that contains the same data.
 *          Only inserted items are copied.
 * @param[in]   original    Pointer to a vector to be copied.
 * @return  Returns the vector structure. Returns NULL in case of failure.
 */
Vector_t *Vector_Copy(const Vector_t *const original);

/**
 * @brief   Erases the content of a vector, allocated memory is freed and the
 *      size of a vector and the count of empty cells is set to 0. The
 *      alloc_step remains unchanged.
 * @param[in]   vector  Pointer to a vector
 */
void Vector_Clear(Vector_t *const vector);

/**
 * @brief   Returns the current length of a vector
 * @param[in]   vector  Pointer to a vector
 * @return  Current length of a vector or UINT64_MAX if vector is NULL. Current length
 *      means number of items in the array (not the amount of allocated items).
 */
uint64_t Vector_Length(const Vector_t *const vector);

/**
 * @brief   Returns the value of a vector at selected position
 * @param[in]   vector      Pointer to a vector
 * @param[in]   position    Position within the vector
 * @param[out]   value       Pointer to a value to be returned in case it is successfully found.
 * @return  TRUE if the item is found in the vector, else returns FALSE
 */
bool Vector_At(const Vector_t *const vector, uint64_t position, uint64_t *const value);

/**
 * @brief   Removes an item at selected position and moves data one item left.
 * @param[in]   vector      Pointer to a vector
 * @param[in]   position    Position within the vector
 * @return  TRUE if position is within the range of vector, else returns FALSE
 */
bool Vector_Remove(Vector_t *const vector, uint64_t position);

/**
 * @brief   Appends a new item to the end of a vector
 * @param[in]   vector  Pointer to a vector
 * @param[in]   value   Value to be inserted
 */
void Vector_Append(Vector_t *const vector, uint64_t value);

/**
 * @brief   Function serves for verification if a value is located in the
 *      vector
 * @param[in]   vector  Pointer to a vector
 * @param[in]   value   Value to be found
 * @return  TRUE if a value is found, else returns FALSE
 */
bool Vector_Contains(const Vector_t *const vector, uint64_t value);

/**
 * @brief   Finds the position of an item described by a value in the vector
 * @param[in]   vector  Pointer to a vector
 * @param[in]   value   Value to be found
 * @param[in]   from    Starting position for searching
 * @return  Position of an item if such value is found, else returns UINT64_MAX
 */
uint64_t Vector_IndexOf(const Vector_t *const vector, uint64_t value, uint64_t from);

/**
 * @brief   Fills a portion of vector specified by a range with a desired
 *          value. Vector is overwritten from the starting to the ending
 *          position (including). If the ending position is located out of
 *          actual vector length borders, vector is filled from the starting
 *          position to the last item of the vector. If the starting position
 *          is located behind the last item of a vector, no changes are made.
 *          #note    Bonus function for active students
 * @param[in]   vector          Pointer to a vector
 * @param[in]   value           Value to be set
 * @param[in]   start_position  Starting position
 * @param[in]   end_position    End position
 */
void Vector_Fill(const Vector_t *const vector, uint64_t value, uint64_t start_position, uint64_t end_position);

/**
 * @brief   Erases all items of a vector and releases the allocated
 *      memory for structure. Pointer to a vector is then set to NULL.
 * @param[in]   vector          Pointer to an adress of a structure that holds the vector
 */
void Vector_Destroy(Vector_t **const vector);

#endif  //__VECTOR_H
