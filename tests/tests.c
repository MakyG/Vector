#include <inttypes.h>
#include <string.h>
#include "minunit.h"
#include "../src/vector.h"

////////////////////////////// IMPORTANT ///////////////////////////////////////
/////////// Source repository: https://github.com/siu/minunit //////////////////
/////////// For more info consult with this page ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

MU_TEST(test_vector_create) {
  Vector_t* v;
  {
    v = Vector_Create(10, 100);
    mu_assert(v != NULL, "Vector should be created for size 10");
  }
  {
    v = Vector_Create(1000000, 100);
    mu_assert(v != NULL, "Vector should be created for size 1000000");
  }
  {
    v = Vector_Create(10000000, 100);
    mu_assert(v != NULL, "Vector should be created for size 10000000");
  }
  {
    v = Vector_Create(4000000000, 100);
    mu_assert(v == NULL, "Vector should not be created for size 4000000000");
  }
}

MU_TEST(test_vector_destroy) {
  Vector_t* v;
  {
    v = Vector_Create(10, 100);
    Vector_Destroy(&v);
    mu_assert(v == NULL, "Destroyed vector should be NULL");
  }
}

MU_TEST(test_vector_copy) {
  Vector_t* v;
  Vector_t* c;
  {
    v = Vector_Create(10, 100);
    c = Vector_Copy(v);
    mu_assert(c != NULL, "Copy should not be NULL");
    mu_assert_int_eq(v->alloc_step, c->alloc_step);
    mu_assert_int_eq(v->free_cells, c->free_cells);
    mu_assert_int_eq(v->size, c->size);
    mu_assert(memcmp(v->items, c->items, (v->size - v->free_cells) * sizeof(v->items[0])) == 0, "The copy of vector should be identical");
    Vector_Destroy(&v);
    Vector_Destroy(&c);
  }
  {
    c = Vector_Copy(NULL);
    mu_assert(c == NULL, "Copy should be NULL");
  }
}

MU_TEST(test_vector_clear) {
  {
    Vector_t* v = Vector_Create(10, 100);
    Vector_Clear(v);
    mu_assert_int_eq(100, v->alloc_step);
    mu_assert_int_eq(0, v->size);
    mu_assert_int_eq(0, v->free_cells);
    mu_assert(v->items == NULL, "Items pointer should be set to NULL");
    Vector_Destroy(&v);
  }
  { Vector_Clear(NULL); }
}

MU_TEST(test_vector_append) {
  Vector_t* v;
  {
    v = Vector_Create(10, 100);
    Vector_Append(v, 10);
    mu_assert_int_eq(10, v->items[0]);
    Vector_Destroy(&v);
  }
  {
    v = Vector_Create(10, 100);
    for (uint64_t i = 0; i < 20; ++i) {
      Vector_Append(v, i);
      mu_assert_int_eq(i, v->items[i]);
    }
    mu_assert_int_eq(110, v->size);
    mu_assert_int_eq(90, v->free_cells);

    Vector_Destroy(&v);
  }
  Vector_Append(NULL, 10);
}

MU_TEST(test_vector_at) {
  Vector_t* v = Vector_Create(10, 100);
  uint64_t val;
  for (uint64_t i = 0; i < 20; ++i) {
    Vector_Append(v, i);
    mu_assert(Vector_At(v, i, &val) == true, "Return from Vector_At should be true");
    mu_assert_int_eq(i, val);
  }
  mu_assert(Vector_At(v, 150, &val) == false, "Out of bounderies Vector_At should return false");
  mu_assert(Vector_At(v, 5, NULL) == false, "Invalid data pointer should to Vector_At should return false");
  Vector_Destroy(&v);
  Vector_Clear(NULL);
}

MU_TEST(test_vector_length) {
  Vector_t* v = Vector_Create(10, 100);
  mu_assert_int_eq(Vector_Length(v), 0);
  Vector_Append(v, 123);
  Vector_Append(v, 123);
  Vector_Append(v, 123);
  mu_assert_int_eq(Vector_Length(v), 3);
  Vector_Destroy(&v);
  mu_assert_int_eq(Vector_Length(NULL), -1);
}

MU_TEST(test_vector_remove) {
  Vector_t* v = Vector_Create(10, 100);
  uint64_t val;
  Vector_Append(v, 123);
  Vector_Append(v, 321);
  Vector_Append(v, 123);
  mu_assert(Vector_Remove(v, 0) == true, "Vector_Remove should return true when position is correct");
  mu_assert(Vector_Remove(v, 2) == false, "Vector_Remove should return false when position is out of boundaries");
  mu_assert_int_eq(Vector_Length(v), 2);
  Vector_At(v, 0, &val);
  mu_assert_int_eq(val, 321);
  Vector_At(v, 1, &val);
  mu_assert_int_eq(val, 123);
  Vector_Destroy(&v);
  mu_assert(Vector_Remove(NULL, 0) == false, "Vector_Remove with NULL pointer should return false");
}

MU_TEST(test_vector_contains) {
  Vector_t* v = Vector_Create(10, 100);
  Vector_Append(v, 123);
  Vector_Append(v, 321);
  Vector_Append(v, 123);
  mu_assert(Vector_Contains(v, 123) == true, "Vector_Contains should return true if data are found");
  mu_assert(Vector_Contains(v, 111) == false, "Vector_Contains should return false if data are not found");
  Vector_Destroy(&v);
  mu_assert(Vector_Contains(NULL, 123) == false, "Vector_Contains with NULL pointer should return false");
}

MU_TEST(test_vector_indexof) {
  Vector_t* v = Vector_Create(10, 100);
  Vector_Append(v, 123);
  Vector_Append(v, 321);
  Vector_Append(v, 123);
  mu_assert_int_eq(Vector_IndexOf(v, 123, 0), 0);
  mu_assert_int_eq(Vector_IndexOf(v, 123, 1), 2);
  mu_assert_int_eq(Vector_IndexOf(v, 111, 0), -1);
  mu_assert_int_eq(Vector_IndexOf(v, 123, 10), -1);
  Vector_Destroy(&v);
  mu_assert_int_eq(Vector_IndexOf(NULL, 123, 0), -1);
}

MU_TEST(test_vector_fill) {
  Vector_t* v = Vector_Create(10, 100);
  uint64_t val;
  for (int i = 0; i < 10; i++) {
    Vector_Append(v, i + 1);
  }

  Vector_Fill(v, 54321, 0, 4);
  for (unsigned int i = 0; i < 5; ++i) {
    Vector_At(v, i, &val);
    mu_assert_int_eq(54321, val);
  }

  for (unsigned int i = 5; i < 10; ++i) {
    Vector_At(v, i, &val);
    mu_assert_int_eq(i + 1, val);
  }

  Vector_Fill(v, 12345, 0, 10);
  for (unsigned int i = 0; i < Vector_Length(v); ++i) {
    Vector_At(v, i, &val);
    mu_assert_int_eq(12345, val);
  }

  Vector_Fill(v, 0, 50, 5);
  for (unsigned int i = 0; i < Vector_Length(v); ++i) {
    Vector_At(v, i, &val);
    mu_assert_int_eq(12345, val);
  }

  Vector_Fill(v, 1, 0, 100);
  for (unsigned int i = 0; i < Vector_Length(v); ++i) {
    Vector_At(v, i, &val);
    mu_assert_int_eq(1, val);
  }
  mu_assert_int_eq(Vector_Length(v), 10);

  Vector_Destroy(&v);
  Vector_Fill(NULL, 123, 0, 10);
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_vector_create);
  MU_RUN_TEST(test_vector_clear);
  MU_RUN_TEST(test_vector_destroy);
  MU_RUN_TEST(test_vector_copy);
  MU_RUN_TEST(test_vector_append);
  MU_RUN_TEST(test_vector_at);
  MU_RUN_TEST(test_vector_length);
  MU_RUN_TEST(test_vector_remove);
  MU_RUN_TEST(test_vector_contains);
  MU_RUN_TEST(test_vector_indexof);
  MU_RUN_TEST(test_vector_fill);
}

int main(void) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return 0;
}
