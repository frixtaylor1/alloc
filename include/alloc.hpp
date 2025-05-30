#ifndef alloc_HPP
#define alloc_HPP

#define interface  struct
#define implements public

typedef unsigned char      int8;
typedef unsigned short     int16;
typedef unsigned int       int32;
typedef unsigned long long int64;
typedef int32              word;
typedef void               heap;
typedef int8               byte;

#define $1 (int8 *)
#define $2 (int16 *)
#define $4 (int32 *)
#define $8 (int64 *)
#define $i (int *)
#define $v (void *)
#define $h (Header *)

extern "C" heap *memspace;

struct alignas(4)
Header {
  Header(): words(0), alloced(false) {
}
  word words : 30;
  bool alloced : 1;
  [[maybe_unused]] bool reserved : 1;
};

Header *next_header(Header *, word);
void *alloc(int32 bytes);
void dealloc(void *ptr);

int main(int, const char**);

#endif // alloc_HPP
