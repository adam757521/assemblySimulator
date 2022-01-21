#include <stdlib.h>
#include <stdio.h>
#include "../../include/list/list.h"

void ListAppend(list_t *self, void *item)
{
    if (self->size == self->used)
    {
        self->size *= 2;
        self->items = realloc(self->items, self->size * sizeof(void *));
    }

    self->items[self->used] = item;
    self->used++;
}

void ListFree(list_t *self, int freeItems)
{
    if (freeItems)
    {
        for (size_t i = 0; i < self->used; i++)
        {
            free(self->items[i]);
        }
    }

    free(self->items);
    free(self);
}

list_t* CreateDynamicList()
{
    list_t* list = malloc(sizeof(list_t));
    list->items = malloc(sizeof(void *));
    list->size = 1;
    list->used = 0;
    return list;
}
