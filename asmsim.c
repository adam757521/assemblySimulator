#include <stdio.h>
#include "list/list.h"

int main()
{
    list_t list = CreateDynamicList();
    ListAppend(&list, "Hello");
    ListAppend(&list, "World");

    printf("%s\n", (const char *)list.items[0]);
    printf("%s\n", (const char *)list.items[1]);

    ListFree(&list, 0);
    return 0;
}