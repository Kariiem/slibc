#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdalign.h>

#include "type.h"


typedef struct {
    len_t len;
    len_t cap;
    len_t sz;
    max_aligned_u8_fa items[];
} fatptr;

fatptr* ptr_to_fatptr(void *p)
{
    return container_of(p, fatptr, items);
}

void *fatptr_to_ptr(fatptr *fp)
{
    return fp->items;
}

void *fatptr_alloc(len_t cnt, len_t size)
{
    len_t nbytes = offsetof(fatptr, items[0].u[cnt * size]);
    fatptr *fp = calloc(nbytes, sizeof(u8));
    fp->cap = cnt;
    fp->sz  = size;
    fp->len = 0;
    return fp->items;
}

void *fatptr_init(len_t cnt, len_t size)
{
    void *p = fatptr_alloc(cnt, size);
    fatptr *fp = ptr_to_fatptr(p);
    fp->len = cnt;
    return fp->items;
}

void *fatptr_realloc(fatptr *f, len_t cnt)
{
    len_t size = f->sz;
    len_t nbytes = offsetof(fatptr, items[0].u[cnt * size]);
    fatptr *fp = realloc(f, nbytes);
    if (fp) fp->cap = cnt;
    return fp;
}

void fatptr_free(void *p)
{
    fatptr *fp = ptr_to_fatptr(p);
    free(fp);
}

len_t fatptr_len(void *p)
{
    fatptr *fp = ptr_to_fatptr(p);
    return fp->len;
}

len_t fatptr_cap(void *p)
{
    fatptr *fp = ptr_to_fatptr(p);
    return fp->cap;
}

void* fatptr_begin(void *p)
{
    fatptr *fp = ptr_to_fatptr(p);
    return (c8 *)fp->items;
}

void* fatptr_end(void *p)
{
    fatptr *fp = ptr_to_fatptr(p);
    return ((c8 *)(fp->items) + fp->len * fp->sz);
}

#define fatptr_append(p, e)                                             \
    do {                                                                \
        fatptr *fp = ptr_to_fatptr(p);                                  \
        if (fp->len >= fp->cap) {                                       \
            fatptr *fpt = fatptr_realloc(fp, 2 * fp->cap);              \
            if (fpt) fp = fpt;                                          \
        }                                                               \
        p = (void*) fp->items;                                          \
        p[fp->len++] =  e;                                              \
    } while(0)
