#ifndef MACRO_H
#define MACRO_H

#define IGNORE(param) ((void)param)

#if defined (__STDC__) && __STDC__
  #if defined (__STDC_VERSION__)
      #if __STDC_VERSION__ < 201112L
        #error C11 support is required
      #endif
  #endif
#endif


#define UNION_FLEX_ARRAY(type, name)            \
    struct {                                    \
        struct {} __unsed;                      \
        type name[];                            \
    }

/* source: offsetof wikipedia's page */
#define container_of(ptr, type, member)                                 \
    ((type *)((char *)(1 ? (ptr) : &((type *)0)->member) - offsetof(type, member)))

#endif /* MACRO_H */
