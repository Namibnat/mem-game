#include <stdlib.h>
#include <unistd.h>
int main()
{
  int ret;
  char *envp[] = { NULL };
  char *argv[] = { "/home/vernon/dev/braintrain.git/bin/mem", "8", NULL };
  ret = execve("/home/vernon/dev/braintrain.git/bin/mem", argv, envp);
  return 0;
}
