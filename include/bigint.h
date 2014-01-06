#ifndef BIGINT_H__
#define BIGINT_H__

#include <stddef.h>
#include <stdbool.h>

struct bigint_t {
  size_t len;
  unsigned long *digits;
};

struct bigint_t bigint_new_empty();
struct bigint_t bigint_new_int(unsigned long);
bool bigint_zero_p(const struct bigint_t *);
bool bigint_eq(const struct bigint_t *, const struct bigint_t *);
struct bigint_t bigint_add(const struct bigint_t *, const struct bigint_t *);
void bigint_pretty_print(const struct bigint_t *);

#endif