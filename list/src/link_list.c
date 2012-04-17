#include "link_list.h"
//create
dlist *list_create(){
    dlist *root = (dlist *)malloc(sizeof(dlist));
    if(root == NULL){
        fprintf(stderr, "malloc failed %s [%d]", __FILE__, __LINE__);
        exit(-1);
    }
    root->prev = NULL;
    root->next = NULL;
    root->data = NULL;
    root->length = 0;
    return root;
}

int list_add(dlist *root, void *data){
    assert(root != NULL);
    if(data == NULL){
        fprintf(stderr, "data is null %s [%d]", __FILE__, __LINE__);
        return LIST_FAILED;
    }

    dlist *new_node = (dlist *)malloc(sizeof(dlist));
    if(new_node == NULL){
        fprintf(stderr, "malloc failed %s [%d]", __FILE__, __LINE__);
        exit(-1);
    }
    new_node->data = data;
    new_node->prev = root;

    if(root->length == 0){
        new_node->next = NULL;
        root->next = new_node;
    }else{
        new_node->next = root->next;
        root->next->prev = new_node;
        root->next = new_node;
    }
    root->length += 1;
    return LIST_OK;
}

void list_print(dlist *root, print_func print_data){
    dlist * p = root->next;
    while(p != NULL){
        print_data(p->data);
        p = p->next;
    }
}

void * list_find_max(dlist *root, cmp_func cmp){
    dlist * p = root->next;
    void *max = p->data;
    while(p != NULL){
        if(cmp(max, p->data) < 0){
            max = p->data;
        }
        p = p->next;
    }
    return max;
}

void list_destroy(dlist *root){
    dlist *q;
    dlist * p = root->next;
    while(p != NULL){
        q = p;
        p = p->next;
        free(q);
        q = NULL;
    }
    free(root);
    root = NULL;
}

static void print_int(void *data){
    printf("%d\n", (int)data);
}

static int cmp_int(void *src, void *dst){
    return ((int)src - (int)dst);
}
int main(int argc, char **argv){
    dlist *list = list_create();
    int i;
    for(i = 1; i <= 10; i++){
        list_add(list, (void *)rand());
    }
    assert(list->length == 10);
    list_print(list, print_int);
    printf("max:%d\n", list_find_max(list, cmp_int));
    list_destroy(list);
}
