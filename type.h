#include <stdint.h>
#include <stddef.h>

#include "macro.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

typedef char c8;

typedef ptrdiff_t len_t;
typedef ptrdiff_t index_t;
typedef ptrdiff_t range_t;

typedef union {
    max_align_t m;
    UNION_FLEX_ARRAY(u8, u);
} max_aligned_u8_fa;
