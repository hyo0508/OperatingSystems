#include "types.h"
#include "user.h"
#include "fcntl.h"

char *argv[] = { "sh", 0 };

int main()
{
  int pid;

  for(;;)
  {
    char username[16] = { 0, };
    char password[16] = { 0, };

    printf(2, "login: ");
    gets(username, 15);
    printf(2, "password: ");
    gets(password, 15);

    username[strlen(username)-1] = 0;
    password[strlen(password)-1] = 0;

    if(success(username, password)) {
      printf(2, "login success\n");
      setusername(username);
      pid = fork();
      if (pid == 0) {
        exec("sh", argv);
      }
      wait();
    } else {
      printf(2, "login failed\n");
    }
  }
}