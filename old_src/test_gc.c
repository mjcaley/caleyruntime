#include <assert.h>
#include <stdlib.h>

#include "gc.h"


void test_gcalloc_destroy()
{
    GCAlloc* g = malloc(sizeof(GCAlloc));
    int* i = malloc(sizeof(int));
    g->ptr = i;

    assert(g != NULL);
    gcalloc_destroy(g);
}

void test_gcalloclist_new()
{
    
}


int main()
{
    test_gcalloc_destroy();
}
