#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <bigint.h>

/* digits[i] < bigint_max */
const unsigned long bigint_max = 1000000000000000000U;

struct bigint_t bigint_new_empty()
{
  return bigint_new_int(0);
}

struct bigint_t bigint_new_int(unsigned long l)
{
  struct bigint_t i;

  if (bigint_max > l)
  {
    i.len = 1;
    i.digits = calloc(1, (sizeof (unsigned long)));
    i.digits[0] = l;
  }
  else
  {
    i.len = 2;
    i.digits = calloc(2, (sizeof (unsigned long)));
    i.digits[0] = l % bigint_max;
    i.digits[1] = (l - i.digits[0]) / bigint_max;
  }

  return i;
}

void bigint_free(const struct bigint_t *i)
{
  free(i->digits);
}

bool bigint_zero_p(const struct bigint_t *i)
{
  unsigned long *digits = i->digits;
  size_t len            = i->len;

  for (int i = 0; i < len; ++i)
    if (digits[i] != 0)
      return false;

  return true;
}

bool bigint_eq(const struct bigint_t *left, const struct bigint_t *right)
{
  size_t max_len = left->len > right->len ? left->len : right->len;

  for (int i = 0; i < max_len; ++i)
  {
    unsigned long left_digit  = left->len   < i + 1 ? 0 : left->digits[i];
    unsigned long right_digit = right->len  < i + 1 ? 0 : right->digits[i];

    if (left_digit != right_digit)
      return false;
  }

  return true;
}

struct bigint_t bigint_add(const struct bigint_t * left, const struct bigint_t * right)
{
  struct bigint_t ret = bigint_new_empty();
  size_t max_len      = left->len > right->len ? left->len : right->len;
  unsigned long *tmp  = realloc(ret.digits, max_len * (sizeof (unsigned long)));
  int carry_up        = 0;

  if (ret.digits != tmp)
  {
    free(ret.digits);
    ret.digits = tmp;
  }

  for (int i = 0; i < max_len; ++i)
  {
    unsigned long left_digit  = left->len   < i + 1 ? 0 : left->digits[i];
    unsigned long right_digit = right->len  < i + 1 ? 0 : right->digits[i];
    unsigned long ret_digit   = left_digit + right_digit + carry_up;

    if (ret_digit < bigint_max)
    {
      ret.digits[i] = ret_digit;
      carry_up = 0;
    }
    else
    {
      ret.digits[i] = ret_digit - bigint_max;
      carry_up = 1;
    }
  }

  if (carry_up)
  {
    tmp           = realloc(ret.digits, (max_len + 1) * (sizeof (unsigned long)));
    ret.len       = max_len + 1;
    tmp[max_len]  = carry_up;

    if (ret.digits != tmp)
    {
      free(ret.digits);
      ret.digits = tmp;
    }
  }
  else {
    ret.len = max_len;
  }

  return ret;
}

void bigint_pretty_print(const struct bigint_t * i)
{
  unsigned long *digits = i->digits;
  size_t len            = i->len;

  printf ("%lu", digits[len - 1]);

  for (int i = 0; i < len - 1; ++i)
  {
    printf ("%018lu", digits[len - i - 2]);
  }
}
