#include "../include/alloc.hpp"
#include <stdio.h>

int main(int argc, const char *argv[]) {
  (void) argc;
  (void) argv;


  void *a = alloc(400);
  dalloc(a);

  void *b = alloc(350);

  void *c = alloc(40);

  dalloc(b);
  printf("%p\n", a);
  printf("%p\n", b);
  printf("%p\n", c);

  return 0;
}
