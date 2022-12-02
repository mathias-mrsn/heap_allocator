#include "../inc/libmalloc.h"
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <commun.h>
#include "slot.h"


#define NB_TEST 100
#define NB_MAX 16000

# ifndef DEBUG
# define DEBUG 0
# endif

/*

int
main () {

// # if (DEBUG == 1)
//     write(5, "salut", 1);
// # endif
    // char *str = malloc(100);

    PUTNBR(sizeof(struct s_slot));
    PUTSTR("\n");


    char *str1 = malloc(100);
    char *str2 = malloc(1000);
    char *str3 = malloc(1000);
    char *str4 = malloc(1000);
    char *str5 = malloc(1000);
    char *str6 = malloc(1000);
    char *str7 = malloc(1000);
    char *str8 = malloc(1000);
    char *str9 = malloc(100000000);

    free(str3);
    free(str4);
    free(str5);
    free(str6);
    free(str7);
    free(str8);
    // free(str2 + 2);
    // char *str6 = malloc(400);

    // free_heap();

    show_alloc_mem();
    char * tmp = realloc(str9, 40000000);
    show_alloc_mem();

    // char *str7 = malloc(400);

    // PUTADDR(str1);
    // PUTSTR("\n");
    // PUTADDR(str2);
    // PUTSTR("\n");
    // PUTADDR(str3);
    // PUTSTR("\n");
    // PUTADDR(str4);
    // PUTSTR("\n");
    // PUTADDR(str5);
    // PUTSTR("\n");
    // PUTADDR(str6);

    // srand(time(NULL));
    // void * ptr;
    // for (int i = 0; i < NB_TEST; i++) {
    //     ptr = malloc(rand() % NB_MAX);
    //     if (!ptr) {
    //         write(1, "error\n", 6);
    //         break;
    //     }
    // }

    return 0;
}

*/

#include <stdio.h>

int main(void)
{
    int *ptr;
    int mb = 1048576;
    int pg_sz = 4096;

    long long int i;

    for (i = 0; i < 1000000000000; i++)
    {
        printf("Trying to allocate %lld MBytes\n", i * pg_sz * sizeof(int) / mb );

        ptr = (int*) calloc(pg_sz, sizeof(int));
        if ( ptr == 0 ) {
            // clean up
            free(ptr);
            printf("Ran out of memory\n");
            return 1;
        }
    }
}