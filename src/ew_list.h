#ifndef __EW_LIST_H__
#define __EW_LIST_H__
#include <stdbool.h>
#include <stddef.h>

typedef void data_eraser_t(void *);

typedef struct ew_lnode {
    void *data;
    struct ew_lnode *next, *prev;
} ew_lnode;

typedef struct ew_list {
    ew_lnode head;
    int size;
    data_eraser_t *data_eraser;
} ew_list;


#define ew_list_foreach(it, list)   \
    for (ew_lnode *it = (list)->head.next, *n = it->next; it != &((list)->head); it = n, n = n->next)


ew_list *ew_list_create(void);
void ew_list_destroy(ew_list *self);
int ew_list_set_data_eraser(ew_list *self, data_eraser_t *data_eraser);
bool ew_list_is_node_exist(ew_list *self, ew_lnode *node);
int ew_list_insert_before(ew_list *self, ew_lnode *pos, void *data);
int ew_list_insert_after(ew_list *self, ew_lnode *pos, void *data);
int ew_list_delete(ew_list *self, ew_lnode *pos);
int ew_list_pushback(ew_list *self, void *data);
int ew_list_popback(ew_list *self);
int ew_list_pushfront(ew_list *self, void *data);
int ew_list_popfront(ew_list *self);
size_t ew_list_size(ew_list *self);
void *ew_list_front(ew_list *self);
void *ew_list_back(ew_list *self);
void ew_lnode_delete(ew_lnode *node);
int ew_lnode_replace(ew_lnode *lhs, ew_lnode *rhs);
int ew_list_remove(ew_list *self, ew_lnode *node);
int ew_list_insert_node_before(ew_list *self, ew_lnode *pos, ew_lnode *node);
int ew_list_insert_node_after(ew_list *self, ew_lnode *pos, ew_lnode *node);
void ew_list_clear(ew_list *self);

#endif // __EW_LIST_H__

