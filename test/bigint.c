#include <stdio.h>
#include "test_helper.h"
#include <bigint.h>

void a_eq_a()
{
  FORALL1("forall a, a = a", a, ({
    bigint_eq(&a, &a);
  }));
}

void a_plus_a_not_eq_a()
{
  FORALL1("forall a, a /= 0 -> a /= a + a", a, ({
    bool r = true;
    struct bigint_t zero  = bigint_new_empty();

    if (bigint_eq(&a, &zero))
      ;
    else {
      struct bigint_t b = bigint_add(&a, &a);
      r = ! bigint_eq(&a, &b);
    }

    r;
  }));
}

void a_plus_b_eq_b_plus_a()
{
  FORALL2("forall a b, a + b = b + a", a, b, ({
    struct bigint_t c = bigint_add(&a, &b);
    struct bigint_t d = bigint_add(&b, &a);
    bigint_eq(&c, &d);
  }));
}

void a_minus_a_eq_zero()
{
  FORALL1("forall a, a - a = 0", a, ({
    struct bigint_t b     = bigint_sub(&a, &a);
    struct bigint_t zero  = bigint_new_empty();
    bigint_eq(&b, &zero);
  }));
}

void a_minus_a_not_eq_a()
{
  FORALL1("forall a, a /= 0 -> a /= a - a", a, ({
    bool r = true;
    struct bigint_t zero  = bigint_new_empty();

    if (bigint_eq(&a, &zero))
      ;
    else {
      struct bigint_t b = bigint_sub(&a, &a);
      r = ! bigint_eq(&a, &b);
    }

    r;
  }));
}

void a_minus_b_not_eq_b_minus_a()
{
  FORALL2("forall a b, a /= b -> a - b /= b - a", a, b, ({
    bool r = true;
    if (bigint_eq(&a, &b))
      ;
    else
    {
      struct bigint_t c = bigint_sub(&a, &b);
      struct bigint_t d = bigint_sub(&b, &a);
      r = ! bigint_eq(&c, &d);
    }
    r;
  }));
}

void a_minus_b_eq_zero_or_b_minus_a_eq_zero()
{
  FORALL2("forall a b, a - b = 0 \\/ b - a = 0", a, b, ({
    struct bigint_t c     = bigint_sub(&a, &b);
    struct bigint_t d     = bigint_sub(&b, &a);
    struct bigint_t zero  = bigint_new_empty();

    bigint_eq(&c, &zero) || bigint_eq(&d, &zero);
  }));
}

void print_super_big_numbers()
{
  printf ("\e[1mWe show testing data.\e[0m\n");
  struct bigint_t a = bigint_new_int(10000000000000000000U);
  struct bigint_t b = bigint_new_int(10000000000000000000U);

  for (int i = 0; i < 100; ++i)
  {
    printf("%d. ", i);
    bigint_pretty_print(&a);
    printf(" + ");
    bigint_pretty_print(&b);
    printf(" = ");
    a = bigint_add(&a, &b);
    b = a;
    bigint_pretty_print(&a);
    printf("\n");
  }
}

int main(int argc, char const *argv[])
{
  a_eq_a();
  a_plus_a_not_eq_a();
  a_plus_b_eq_b_plus_a();
  a_minus_a_eq_zero();
  a_minus_a_not_eq_a();
  a_minus_b_not_eq_b_minus_a();
  a_minus_b_eq_zero_or_b_minus_a_eq_zero();
  // print_super_big_numbers();
  return 0;
}