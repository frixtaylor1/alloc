#include "../include/alloc.hpp"
#include <assert.h>

static byte *lastAddress = ($1 memspace + (1024 * 1024 * 1024));

Header *next_header(Header *header) {
  return $h ($1 (header + 1) + header->words * 4);
}

Header *find_block(Header *current, word wordsToAlloc) {
  if ($1 current >= lastAddress) {
    return nullptr;
  }
  if (!current->alloced) return current;

  return find_block(next_header(current), wordsToAlloc);
}

void *alloc(int32 bytes) {
  void   *mem         = memspace;
  Header *header      = $h mem;
  word   wordsToAlloc = !(bytes % 4) ? bytes / 4 : bytes / 4 + 1;

  if (!bytes) return nullptr;

  if (!header->alloced) {
    if (header->words == 0) {
      header->words = wordsToAlloc;
      header->alloced = true;
      header->reserved = false;
      return $h mem + 1;
    }

    if (header->words >= wordsToAlloc) {
      Header *next   = next_header(header);
      next->words    = wordsToAlloc;
      next->alloced  = false;
      next->reserved = false;

      header->words = wordsToAlloc;
      header->alloced = true;
      return $v (header + 1);
    }
  }

  Header *found = find_block(header, wordsToAlloc);
  if (found) {
    found->alloced = true;
    return $v (found + 1);
  }

  assert(false && "Error no mem!");
}

void dealloc(void *ptr) {
  (void) ptr;
  assert(false && "MUST IMPLEMENT!");
}

int main(int argc, const char *argv[]) {
  (void) argc;
  (void) argv;

  int32 *a = (int32 *)alloc(4);
  *a = 10;

  int32 *b = (int32 *)alloc(4);
  *b = 11;

  int32 *c = (int32 *)alloc(4);
  *c = 11;

  dealloc(a);
  dealloc(b);
  dealloc(c);

  return 0;
}
