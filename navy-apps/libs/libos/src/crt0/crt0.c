#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[], char *envp[]);
extern char **environ;
void call_main(uintptr_t *args) {
  char *empty[] =  {NULL };
  environ = empty;
	int argc = *(int *)args;
	char **argv = (char **)(args + sizeof(int));
	char **envp = (char **)(args + sizeof(int) + sizeof(char**));
  exit(main(argc, argv, envp));
  assert(0);
}
