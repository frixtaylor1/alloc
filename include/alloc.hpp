#ifndef alloc_HPP
#define alloc_HPP

#define interface  struct
#define implements public

#define $visible __attribute__((visibility ("default")))
#define $hidden static

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

extern "C" heap *memspace;

/**
 * Allocates
 *
 * @param int32  bytes
 *
 * return void *
 */
extern "C" $visible void *alloc(int32 bytes);

/**
 * Reallocs given current ptr and new size
 *
 * @param void * ptr
 * @param int32  bytes
 *
 * return void
 */
extern "C" $visible void *ralloc(void *, int32);

/**
 * Free or deallocates given a ptr
 *
 * @param void * ptr
 *
 * return void
 */
extern "C" $visible void dalloc(void *);

int main(int, const char**);

#endif // alloc_HPP
