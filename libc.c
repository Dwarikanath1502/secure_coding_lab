// LIBC attack

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>  // for uintptr_t

#ifndef BUF_SIZE
#define BUF_SIZE 12
#endif

int bof(char *str)
{
    char buffer[BUF_SIZE];
    uintptr_t *framep;

    // Copy rbp into framep (64-bit architecture)
    asm("movq %%rbp, %0" : "=r" (framep));      

    /* print out information for experiment purpose */
    printf("Address of buffer[] inside bof():  0x%.16lx\n", (uintptr_t)buffer);
    printf("Frame Pointer value inside bof():  0x%.16lx\n", (uintptr_t)framep);

    strcpy(buffer, str);   

    return 1;
}

void foo(){
    static int i = 1;
    printf("Function foo() is invoked %d times\n", i++);
    return;
}

int main(int argc, char **argv)
{
   char input[1000];
   FILE *badfile;

   badfile = fopen("badfile", "r");
   if (badfile == NULL) {
       perror("Error opening file");
       return 1;
   }
   int length = fread(input, sizeof(char), 1000, badfile);
   printf("Address of input[] inside main():  0x%lx\n", (uintptr_t) input);
   printf("Input size: %d\n", length);

   bof(input);

   printf("(^_^)(^_^) Returned Properly (^_^)(^_^)\n");
   return 1;
}
