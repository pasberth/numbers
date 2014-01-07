#include <stdio.h>
#include <bigint.h>

int main(int argc, char const *argv[])
{
  struct bigint_t zero  = bigint_new_empty();
  struct bigint_t one   = bigint_new_int(1);
  struct bigint_t nat   = zero;

  while (true)
  {
    bigint_pretty_print(&nat);
    printf("\n");
    struct bigint_t tmp = bigint_add(&nat, &one);
    bigint_free(&nat);
    nat = tmp;
  }

  bigint_free(&zero);
  bigint_free(&one);
  bigint_free(&nat);
  return 0;
}