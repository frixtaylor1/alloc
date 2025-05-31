#include "../include/alloc.hpp"
#include <assert.h>
#include <string.h>

$hidden
byte *lastAddress = ($1 memspace + (1024 * 1024 * 1024));

struct alignas(4)
Header {
  Header(): words(0), alloced(false) {
}
  word words : 30;
  bool alloced : 1;
  [[maybe_unused]] bool reserved : 1;
};

#define $h (Header *)


$hidden
word _calculate_words_given_bytes(int32 bytes) {
  return !(bytes % 4) ? bytes / 4 : bytes / 4 + 1;
}

$hidden
Header *_get_header_given_ptr(void *ptr) {
  return $h ptr - 1;
}

$hidden
int32 _get_bytes_alloc_region_given_header(Header *header) {
  return header->words * 4;
}

$hidden
Header *_next_header(Header *header) {
  return $h ($1 (header + 1) + header->words * 4);
}

$hidden
Header *_find_block(Header *current, word wordsToAlloc) {
  if ($1 current >= lastAddress) {
    return nullptr;
  }
  if (!current->alloced) return current;

  return _find_block(_next_header(current), wordsToAlloc);
}

$visible
void *alloc(int32 bytes) {
  void   *mem         = memspace;
  Header *header      = $h mem;
  word   wordsToAlloc = _calculate_words_given_bytes(bytes);

  if (!bytes) return nullptr;

  if (!header->alloced) {
    if (header->words == 0) {
      header->words = wordsToAlloc;
      header->alloced = true;
      header->reserved = false;
      return $h mem + 1;
    }

    if (header->words >= wordsToAlloc) {
      Header *next   = _next_header(header);
      next->words    = wordsToAlloc;
      next->alloced  = false;
      next->reserved = false;

      header->words = wordsToAlloc;
      header->alloced = true;
      return $v (header + 1);
    }
  }

  Header *found = _find_block(header, wordsToAlloc);
  if (found) {
    found->alloced = true;
    return $v (found + 1);
  }

  assert(false && "Error no mem!");
}

$visible
void dalloc(void *ptr) {
  Header *header = _get_header_given_ptr(ptr);

  if (!header->alloced) assert(header->alloced && "Double free! %d");
  header->alloced = 0;

  ::memset(ptr, 0, _get_bytes_alloc_region_given_header(header));
}

$visible
void *ralloc(void *ptr, int32 bytes) {
  Header *header = _get_header_given_ptr(ptr);

  word wordsNeeded = _calculate_words_given_bytes(bytes);
  if (header->words >= wordsNeeded) {
    header->words = wordsNeeded;
    return ptr;
  }

  dalloc(ptr);

  return alloc(bytes);
}
