#include <stdlib.h>
#include "list.h"

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

    self->items = NULL;
    self->size = self->used = 0;
}

list_t CreateDynamicList()
{
    list_t list;
    list.items = malloc(sizeof(void *));
    list.size = 1;
    list.used = 0;
    return list;
}
