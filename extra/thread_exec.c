#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_THREAD 5

void *thread_main(void *arg)
{
  int val = (int)arg;
  printf(1, "Thread %d start\n", val);
  if (arg == 0) {
    sleep(100);
    char *pname = "/hello_thread";
    char *args[2] = {pname, 0};
    printf("Executing...\n");
    execl(pname, args);
  }
  else {
    sleep(200);
  }
  
  printf("This code shouldn't be executed!!\n");
  exit(0);
  return 0;
}

pthread_t thread[NUM_THREAD];

int main(int argc, char *argv[])
{
  int i;
  printf("Thread exec test start\n");
  for (i = 0; i < NUM_THREAD; i++) {
    pthread_create(&thread[i], NULL, thread_main, (void *)i);
  }
  sleep(200);
  printf("This code shouldn't be executed!!\n");
  exit(0);
}
