// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

// Interface functions:
// 1) Function for creation and addition
void StringListInit(char*** list);
void StringListAdd(char** list, char* str);
// 2) Functions for destruction and deletion
void StringListDestroy(char*** list);
void StringListRemove(char** list, char* str);
void StringListRemoveDuplicates(char** list);
// 3) Functions for list management
void StringListReplaceInStrings(char** list, const char* before, char* after);
void StringListSort(char** list);
// 4) Safe output functions
void PrintAllStrings(char** list);
void PrintByIndex(char** list, size_t indx);
// 5) Other
size_t StringListSize();
size_t StringListIndexOf(char** list, const char* str);

// Helper functions
void Shift(char** list, size_t indx);
int CompareStrings(char* a, char* b);

size_t size = 0;
const size_t capacity = 16;
size_t capacity_mult = 1;

int main()
{
    char** list = NULL;
    StringListInit(&list);

    StringListAdd(list, "cookie");
    StringListAdd(list, "asphalt");
    StringListAdd(list, "boost");
    StringListAdd(list, "beast");
    StringListAdd(list, "beast");
    StringListAdd(list, "cream");
    StringListAdd(list, "dungeon");

    printf("\n---UNSORTED---:\n");
    PrintAllStrings(list);

    size_t item_indx = StringListIndexOf(list, "boost");
    printf("\nIndex of 'boost' == %zu\n", item_indx);

    printf("Size of list before item named 'cream' removal: %zu\n", StringListSize());
    StringListRemove(list, "cream");

    printf("Size of list after item named 'cream' removal: %zu\n", StringListSize());

    printf("Size of list before removal of duplicates: %zu\n", StringListSize());
    StringListRemoveDuplicates(list);
    printf("Size of list after removal of duplicates: %zu\n", StringListSize());

    printf("\nReplace element 'dungeon' with 'Dijkstra'\n");
    StringListReplaceInStrings(list, "dungeon", "Dijkstra");

    printf("\n---SORTED---:\n");

    StringListSort(list);
    PrintAllStrings(list);

    PrintByIndex(list, 2);

    StringListDestroy(&list);
}

void StringListInit(char*** list)
{
    *list = (char **)malloc(capacity * sizeof(char *));
}

void StringListDestroy(char*** list)
{
    free(*list);
    size = 0;
    capacity_mult = 1;
}

void StringListAdd(char** list, char* str)
{
    list[size] = str;

    if(size + 1 == capacity)
    {
        capacity_mult *= 2;
        char** tmp = NULL;
        tmp = (char **)realloc(list, capacity * capacity_mult * sizeof (char*));
        if(tmp == NULL)
        {
            exit(-1); // failed to realloc
        }
        list = tmp;
    }

    size++;
    list[size] = NULL;
}

size_t StringListSize()
{
    return size;
}
size_t StringListIndexOf(char** list, const char* str)
{
    for(size_t i = 0; i < size; i++)
    {
        if(list[i] == str)
            return i;
    }
    return -1;
}

void StringListRemove(char** list, char* str)
{
    size_t indx;
    while((indx = StringListIndexOf(list,str)) != -1)
    {
        list[indx] = NULL;
        Shift(list, indx);
        size--;
    }
}
void Shift(char** list, size_t indx)
{
    for(size_t i = indx; i < size - 1; i++)
    {
        list[i] = list[i+1];
        list[i+1] = NULL;
    }
}

void StringListRemoveDuplicates(char** list)
{
    char** tmp_list = (char **)malloc(capacity * capacity_mult * sizeof(char *));

    size_t tmp_size = 0;
    for(size_t i = 0; i < size; i++)
    {
        if(StringListIndexOf(tmp_list, list[i]) == -1)
        {
            tmp_list[tmp_size] = list[i];
            tmp_size++;
        }
    }
    free(list);
    memcpy(list, tmp_list, tmp_size-1 * sizeof(char *));
    size = tmp_size;
}

void StringListReplaceInStrings(char** list, const char* before, char* after)
{
    for(size_t i = 0; i < size; i++)
    {
        if(list[i] == before)
            list[i] = after;
    }
}

int CompareStrings(char* a, char* b)
{
    return strcmp(a, b) > 0;
}

void StringListSort(char** list)
{
    int swapped;
    for(size_t i = 0; i < size - 1; i++)
    {
        swapped = 0;
        for(size_t j = 0; j < size - 1 - i; j++)
        {
            if(CompareStrings(list[j], list[j + 1]))
            {
                char* buff = list[j + 1];
                list[j + 1] = list[j];
                list[j] = buff;
                swapped = 1;
            }
        }
        if(!swapped)
            break;
    }
}

void PrintAllStrings(char** list)
{
    for(size_t i = 0; i < size; i++)
    {
        printf("%zu) %s\n", i + 1, list[i]);
    }
}
void PrintByIndex(char** list, size_t indx)
{
    if(indx < size)
        printf("Item by index %zu == %s", indx, list[indx]);
}