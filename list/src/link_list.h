/*
 * 双向链表实现
 *
 */

#ifndef __LINK_LIST__
#define __LINK_LIST__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef enum{
    LIST_FAILED = -1,
    LIST_OK = 0
}LIST_RET;

typedef struct _l_node{
    struct _l_node *prev;
    struct _l_node *next;
    void *data;
    size_t length;
}dlist;

typedef void (*print_func)(void* data);
typedef int (*cmp_func)(void* src, void *dst);

dlist *list_create();
LIST_RET list_add(dlist *root, void *data);
void list_print(dlist *root, print_func print_data);
void list_destroy(dlist *root);
void * list_find_max(dlist *root, cmp_func cmp);

#endif
