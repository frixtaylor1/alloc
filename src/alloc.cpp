#include "../include/alloc.hpp"

#include <assert.h>

void *alloc(int32 bytes) {
  assert(false && "NOT IMPLEMENTED!");
  return nullptr;
}

void dealloc(void *ptr) {
  assert(false && "NOT IMPLEMENTED!");
}

int main(int argc, const char *argv[]) {
  alloc(32);

  return 0;
}
