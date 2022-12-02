#include <stdio.h>
#include <stdlib.h>

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

/*

MY MALLOC : 18.4s for 200Mb
REEL MALLOC : 40.2s for 200Mb

*/