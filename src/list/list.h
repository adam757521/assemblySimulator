#ifndef ASMVM_LIST_H
#define ASMVM_LIST_H

typedef struct
{
    void **items;
    size_t size;
    size_t used;
} list_t;

void ListAppend(list_t *self, void *item);
void ListFree(list_t *self, int freeItems);
list_t* CreateDynamicList();
#endif
