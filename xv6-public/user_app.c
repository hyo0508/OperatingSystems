#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
  int pid = fork();
  if (pid < 0) {
    printf(1, "fork error.\n");
  } else if (pid == 0) {
    for (int i = 0;i < 10000; i++) printf(1, "Child\n");
  } else {
    for (;;) printf(1, "Parent\n");
  }
  exit();
}