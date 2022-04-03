#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
  int pid;
  pid = fork();
  if (pid < 0) {
    printf(1, "fork error.\n");
  } else if (pid == 0) {
    for (;;) {
      printf(1, "Child\n");
      yield();
    }
  } else {
    for (;;) {
      printf(1, "Parent\n");
      yield();
    }
  }
  exit();
}