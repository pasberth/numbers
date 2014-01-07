#include <stdio.h>
#include <bigint.h>

int main(int argc, char const *argv[])
{
  struct bigint_t a = bigint_new_empty();
  struct bigint_t b = bigint_new_int(1);

  bigint_pretty_print(&a);
  printf("\n");
  bigint_pretty_print(&b);
  printf("\n");

  while (true)
  {
    struct bigint_t c = bigint_add(&a, &b);
    bigint_pretty_print(&c);
    printf("\n");
    bigint_free(&a);
    a = b;
    b = c;
  }

  return 0;
}