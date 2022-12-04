#include "../inc/libmalloc.h"
#include <unistd.h>
#include <math.h>
#include <time.h>
// #include <stdlib.h>
#include <commun.h>
#include "slot.h"


#define NB_TEST 100
#define NB_MAX 16000

# ifndef DEBUG
# define DEBUG 0
# endif

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

    // free(str3 + 10);
    free(str4);
    free(str5);
    free(str5);
    free(str6);
    free(str7);
    // free(str8 + 100);
    // free(str9 + 100);
    // free(str8);
    // free(str2 + 2);
    // char *str6 = malloc(400);

    /*    SEGV      */

    // slot * s = NULL;

    // PUTNBR(s->state);

    // free_heap();

    // char * tmp = realloc(str9, 40000000);
    str3 = realloc(str3, 1300);
    show_alloc_mem();

    char * str10 = malloc(257);

    show_alloc_mem();

    // show_alloc_mem();

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