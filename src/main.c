#include "malloc.h"

int
main () {
    char *str = malloc(100);
    char *str1 = malloc(100);
    // char *str2 = malloc(1000);
    // char *str3 = malloc(1000);
    // char *str4 = malloc(1000);
    // char *str5 = malloc(1000);
    return 0;
}

// #include <stdio.h>
// #include <unistd.h>
// #include <sys/mman.h>
// #include <stdlib.h>

// int main()
// {

//     int N=5;
//     // int *ptr;
//     int *ptr = mmap ( NULL, N*sizeof(int),
//     PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0 );
//     // int *ptr = malloc(N*sizeof(int));

//     // if(ptr == MAP_FAILED){
//     //     printf("Mapping Failed\n");
//     //     return 1;
//     // }

//     for(int i=0; i<N; i++)
//         ptr[i] = i*10;

//     for(int i=0; i<N; i++) {
//         // printf("[%d] ",ptr[i]);
//         write(1, "|\n", 2);
//     }

//     // printf("[%ls]\n", &ptr[0] + 5000);

//     // printf("\n");
//     // int err = munmap(ptr, 10*sizeof(int));
//     // if(err != 0){
//     //     printf("UnMapping Failed\n");
//     //     return 1;
//     // }

//     return 0;
// }
