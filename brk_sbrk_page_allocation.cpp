#include <stdio.h>
#include <unistd.h>

int main()
{
    long int page_size = sysconf(_SC_PAGESIZE);
    printf("Page size: %ld\n", page_size);
    
    void* c1 = sbrk(0);
    printf("initial heap break address: %p\n", c1);

    printf("sizeof char: %lu\n", sizeof(char));
    c1 = (void*) ((char*) c1 + 1);
    printf("c1: %p\n", c1);

    brk(c1);

    void* c2 = sbrk(0);
    printf("c2: %p\n", c2);            
    
   char x = *((char*) c1 - 1 + (_SC_PAGESIZE - 1)); // ok
    // char x = *((char*) c1 - 1 + 4095); seg fault
}
