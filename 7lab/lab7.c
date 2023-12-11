#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

int main() 
{
  void *handle;
  int (*func)(void);
  char *error;
    handle = dlopen("liblab5.so", RTLD_LAZY);
    if (handle == NULL) {
        printf("Не удалось открыть библиотеку: %s\n", dlerror());
        return 1;
    }

  func = dlsym(handle, "printMenu");
  if ((error = dlerror()) != NULL)  {
    fputs(error, stderr);
    exit(1);
  }

  printf ("%d\n", (*func)());
  dlclose(handle);
  return 0;
}