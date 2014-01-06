#include <stdio.h>
#include "test_helper.h"
#include <bigint.h>

void a_eq_a()
{
  FORALL1("forall a, a = a", a, ({
    bigint_eq(&a, &a);
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
  a_plus_b_eq_b_plus_a();
  // print_super_big_numbers();
  return 0;
}