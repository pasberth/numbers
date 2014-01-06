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
    nat = bigint_add(&nat, &one);
  }
  return 0;
}