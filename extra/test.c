#include <stdio.h>

#define PGSIZE 8
#define PGROUNDUP(sz)  (((sz)+PGSIZE-1) & ~(PGSIZE-1))

int main() {
    for (int i = 0; i < 32; i++) {
        printf("sz=%2d, PGROUNDUP(sz)=%2d\n", i, PGROUNDUP(i));
    }
}