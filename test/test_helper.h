#ifndef TEST_HELPER_H__
#define TEST_HELPER_H__

#define FORALL2(title, a, b, test)                              \
  printf ("%s%s%s", "\e[1m", title, "\e[0m\n");                 \
  for ( unsigned long i = 0;                                    \
        i < 10000000000000000000U;                              \
        i += 100000000000000000U)                               \
  {                                                             \
    for ( unsigned long j = 0;                                  \
          j < 10000000000000000000U;                            \
          j += 1000000000000000000U)                            \
    {                                                           \
      struct bigint_t a = bigint_new_int(i);                    \
      struct bigint_t b = bigint_new_int(j);                    \
      if (test)                                                 \
      {                                                         \
        printf("\e[32m.\e[0m");                                 \
      }                                                         \
      else                                                      \
      {                                                         \
        printf("\e[31m.\e[0m");                                 \
      }                                                         \
    }                                                           \
  }                                                             \
  printf("\n");

#define FORALL1(title, a, test) FORALL2(title, a, _2, test)

#endif