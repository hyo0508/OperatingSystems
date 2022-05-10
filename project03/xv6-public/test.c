#include "types.h"
#include "stat.h"
#include "user.h"

void* thread_func(void* arg) {
    int val = (int)arg;
    printf(1, "val: %d\n", val);
    thread_exit(arg);
    return 0;
}

int main(int argc, char* argv[]) {
    thread_t thread;
    int val = 0;
    int retval;

    for (int i = 0; i < 1000; i++) {
        thread_create(&thread, thread_func, &val);
        thread_join(thread, (void**)&retval);
    }
    exit();
}