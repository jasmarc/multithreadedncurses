#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "test.h"

#define TRUE 1
#define FALSE 0

int tests_run = 0;

static char * test_sleep_random() {
    // srand(time(NULL));
    // sleep(3 + (rand() % 5));
    int i;
    for(i = 0; i < 20; ++i)
    {
        printf("%d\n", rand());
    }
    return 0;
}

static char * all_tests() {
    mu_run_test(test_sleep_random);
    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if(result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
