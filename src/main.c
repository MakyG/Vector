#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include "ioutils.h"
#include "vector.h"

#define GET_LONG_AND_TEST(VAR)   \
  run = io_utils_get_long(&VAR); \
  if (!run) {                    \
    break;                       \
  }

int main(void) {
  bool run = true;
  long n;
  printf(
      "Vector test program\n"
      "Type the default size of array and the size of incrementation.\n"
      "Size:\n");
  Vector_t *vector;
  {
    long size, step;

    if (io_utils_get_long(&size) == false) {
      return 0;
    }

    printf("Incrementation:\n");

    if (io_utils_get_long(&step) == false) {
      return 0;
    }

    vector = Vector_Create((uint64_t)size, (uint32_t)step);
  }

  if (vector == NULL) {
    printf("Memory for vector was not allocated successfully.\n");
    return 0;
  }

  for (uint32_t val = 0; val < 100; val += 5) {
    Vector_Append(vector, val);
  }

  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  while (run) {
    printf(
        "Press:\n"
        "1 to show the length of vector\n"
        "2 to add a new item\n"
        "3 to remove an item\n"
        "4 to print all items\n"
        "5 to find out whether an item is present\n"
        "6 to find an item's position\n"
        "7 to clear the vector\n"
        "8 to fill a portion of the vector with desired value\n"
        "9 to create a copy of a vector\n"
        "0 to print one item\n"
        "anything else to finish.\n");
    char c;

    if (io_utils_get_char(&c) == false) {
      break;
    }

    switch (c) {
      case '1':
        printf("Vector length: %" PRIu64 "\n", Vector_Length(vector));
        break;

      case '2':
        printf("Choose the value of an item:\n");
        GET_LONG_AND_TEST(n)
        Vector_Append(vector, (uint64_t)n);
        break;

      case '3':
        printf("Choose the position of an item to be removed:\n");
        GET_LONG_AND_TEST(n)
        Vector_Remove(vector, (uint64_t)n);
        break;

      case '4':
        if (Vector_Length(vector) != UINT64_MAX) {
          for (uint64_t i = 0; i < Vector_Length(vector); i++) {
            uint64_t elm;

            if (Vector_At(vector, i, &elm)) {
              printf("vector[%" PRIu64 "]: %" PRIu64 "\n", i, elm);
            } else {
              printf("Item at position %" PRIu64
                     " was not found within the vector.\n",
                     i);
            }
          }
        }

        break;

      case '5':
        printf("Choose the value of an item to be found:\n");
        GET_LONG_AND_TEST(n)

        if (Vector_Contains(vector, (uint64_t)n)) {
          printf("Vector contains this item.\n");
        } else {
          printf("Vector does not contain this item.\n");
        }

        break;

      case '6':
        printf("Choose the value of an item to be found:\n");
        GET_LONG_AND_TEST(n)
        long index;
        printf("Choose the initial index for searching:\n");
        GET_LONG_AND_TEST(index)
        uint64_t position =
            Vector_IndexOf(vector, (uint64_t)n, (uint64_t)index);
        if (position != UINT64_MAX) {
          printf("Position of an item: %" PRIu64 "\n", position);
        } else {
          printf("Position of an item: not found\n");
        }
        break;

      case '7':
        Vector_Clear(vector);
        break;

      case '8':
        printf("Choose the value to be inserted:\n");
        long val = 0;
        GET_LONG_AND_TEST(val)
        printf("Choose the starting position:\n");
        long begin = 0;
        GET_LONG_AND_TEST(begin)
        printf("Choose the end position:\n");
        long end = 0;
        GET_LONG_AND_TEST(end)
        Vector_Fill(vector, (uint64_t)val, (uint64_t)begin, (uint64_t)end);
        break;

      case '9': {
        Vector_t *copy = Vector_Copy(vector);

        if (copy != NULL) {
          if (Vector_Length(copy) != UINT64_MAX) {
            for (uint64_t i = 0; i < Vector_Length(copy); i++) {
              uint64_t elm;

              if (Vector_At(copy, i, &elm)) {
                printf("copy[%" PRIu64 "]: %" PRIu64 "\n", i, elm);
              } else {
                printf("Item at position %" PRIu64
                       " was not found within the vector.\n",
                       i);
              }
            }
          }

          printf("Removing the vector \"copy\"\n");
          Vector_Destroy(&copy);
        }
      } break;

      case '0': {
        printf("Choose the value of index to be found: \n");
        long i = 0;
        GET_LONG_AND_TEST(i);
        uint64_t elm;

        if (Vector_At(vector, i, &elm)) {
          printf("vector[%ld]: %" PRIu64 "\n", i, elm);
        } else {
          printf("Item at position %ld was not found within the vector.\n", i);
        }
      } break;

      default:
        run = false;
        break;
    }
  };

  printf("Freeing all allocated memory.\n");

  Vector_Destroy(&vector);

  printf("All allocated memory was freed.\n");

  return 0;
}
