#include <stdio.h>

#include "fatptr.h"

int main()
{
    int *ip = fatptr_alloc(10, sizeof(*ip));
    for (int *itr = fatptr_begin(ip); itr != fatptr_end(ip); ++itr) {
        *itr = itr - ip;
    }
    for (int *itr = fatptr_begin(ip); itr != fatptr_end(ip); ++itr) {
        printf("ip[%ld] = %d\n", (itr - ip), *itr);
    }
    for (int i = 0; i < 50; ++i) fatptr_append(ip, i<<1);
    printf("len: %ld, cap: %ld\n", fatptr_len(ip), fatptr_cap(ip));

    for (int *itr = fatptr_begin(ip); itr != fatptr_end(ip); ++itr) {
        printf("ip[%ld] = %d\n", (itr - ip), *itr);
    }

    fatptr_free(ip);
    return 0;
}
