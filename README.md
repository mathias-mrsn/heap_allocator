## Warning

The sharing of this project on my GitHub aims to help peoples to open their minds to new logics or help peoples in case of difficulty. In no way, that aims to copy and paste this work on your own repository.

# malloc

**malloc** is a project that aims to recreate functions from the `stdlib.h` library.

## Functions

```c
// Mandatory functions
void * malloc (size_t len);
void free (void * ptr);
void *  realloc (void * ptr, size_t len);
void show_alloc_mem (void);

// Bonus functions

void show_alloc_mem_ex (void);
// void defragmentation (void);

// My functions

void free_heap (void);
[...]
```

## Defines

```c
// All those defines can be changed into the Makefile by changing 0 with 1.

#define DEBUG; 
// If set the program will print information about malloc and free calls.

#define LEAK_SAFETY;
// If set the program will automatically free every leaks at the end of the program.

#define CHECK_ALL;
// If set the program will add more information for each malloc, free or realloc calls.
// You will be able to detailed every leaks (file, line number, function)

#define LEAKS;
// If set the program will automatically print every leaks at the end of the program

```

## Usage

```shell
// You must include "inc/libmalloc.h" in your C program.

$> gcl https://github.com/mathias-mrsn/malloc.git
$> cd malloc
$> make
$> cd mains
$> gcc exemple.c ../malloc.so
```


TODO:
- [ ] defragmentation function

