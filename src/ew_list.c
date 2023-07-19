#include "ew_list.h"
#include <stdlib.h>




ew_list *ew_list_create(void)
{
    ew_list *self = (ew_list *)malloc(sizeof(ew_list));
    if (!self) {
        return NULL;
    }
    self->head.data = NULL;
    self->head.prev = self->head.next = &self->head;
    self->size = 0;
    self->data_eraser = NULL;
    return self;
}

void ew_list_destroy(ew_list *self)
{
    if (!self) {
        return ;
    }
    ew_list_foreach(it, self) {
        if (self->data_eraser) {
            self->data_eraser(it->data);
        }
        free(it);
    }
   free(self);
}

void ew_list_clear(ew_list *self)
{
    if (!self) {
        return ;
    }
    ew_list_foreach(it, self) {
        ew_lnode_delete(it);
        if (self->data_eraser) {
            self->data_eraser(it->data);
        }
        free(it);
        self->size -= 1;
    }
}

int ew_list_set_data_eraser(ew_list *self, data_eraser_t *data_eraser)
{
    if (!self || !data_eraser) {
        return -1;
    }
    self->data_eraser = data_eraser;
    return 0;
}

bool ew_list_is_node_exist(ew_list *self, ew_lnode *node)
{
    if (!self || !node) {
        return false;
    }
    if (node == &self->head) {
        return true;
    }
    ew_list_foreach(it, self) {
        if (it == node) {
            return true;
        }
    }
    return false;
}

static ew_lnode *ew_lnode_new(ew_lnode *prev, ew_lnode *next, void *data)
{
    if (!data || !prev || !next) {
        return 0;
    }
    ew_lnode *lnode = (ew_lnode *)malloc(sizeof(ew_lnode));
    if (!lnode) {
        return NULL;
    }
    lnode->data = data;
    lnode->prev = prev;
    lnode->next = next;
    prev->next = lnode;
    next->prev = lnode;
    return lnode;
}

static void ew_lnode_insert(ew_lnode *prev, ew_lnode *next, ew_lnode *node)
{
    node->prev = prev;
    node->next = next;
    prev->next = node;
    next->prev = node;
}

int ew_list_insert_node_before(ew_list *self, ew_lnode *pos, ew_lnode *node)
{
    if (!self || !pos || !node) {
        return -1;
    }
    ew_lnode_insert(pos->prev, pos, node);
    self->size += 1;
    return 0;
}

int ew_list_insert_node_after(ew_list *self, ew_lnode *pos, ew_lnode *node)
{
    if (self || !pos || !node) {
        return -1;
    }
    ew_lnode_insert(pos, pos->prev, node);
    self->size += 1;
    return 0;
}

int ew_list_insert_before(ew_list *self, ew_lnode *pos, void *data)
{
    if (!self || !pos || !data) {
        return -1;
    }
    if (!ew_list_is_node_exist(self, pos)) {
        return -2;
    }
    if (!ew_lnode_new(pos->prev, pos, data)) {
        return -3;
    }
    self->size += 1;
    return 0;
}

int ew_list_insert_after(ew_list *self, ew_lnode *pos, void *data)
{
    if (!self || !pos || !data) {
        return -1;
    }
    if (!ew_list_is_node_exist(self, pos)) {
        return -2;
    }
    if (!ew_lnode_new(pos, pos->next, data)) {
        return -3;
    }
    self->size += 1;
    return 0;
}

void ew_lnode_delete(ew_lnode *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

int ew_lnode_replace(ew_lnode *lhs, ew_lnode *rhs)
{
    if (!lhs || !rhs) {
        return -1;
    }
    ew_lnode *temp = NULL;
    lhs->prev->next = rhs;
    rhs->prev->next = lhs;
    lhs->next->prev = rhs;
    rhs->next->prev = lhs;
    temp = lhs->prev;
    lhs->prev = rhs->prev;
    rhs->prev = temp;
    temp = lhs->next;
    lhs->next = rhs->next;
    rhs->next = temp;
    return 0;
}

int ew_list_remove(ew_list *self, ew_lnode *node)
{
    if (!self || !node) {
        return -1;
    }
    if (!ew_list_is_node_exist(self, node)) {
        return -2;
    }
    ew_lnode_delete(node);
    self->size -= 1;
    return 0;
}

int ew_list_delete(ew_list *self, ew_lnode *node)
{
    if (!self || !node) {
        return -1;
    }
    if (!ew_list_is_node_exist(self, node)) {
        return -2;
    }
    ew_lnode_delete(node);
    if (self->data_eraser) {
        self->data_eraser(node->data);
    }
    free(node);
    self->size -= 1;
    return 0;
}


int ew_list_pushback(ew_list *self, void *data)
{
    return ew_list_insert_before(self, &self->head, data);
}

int ew_list_pushfront(ew_list *self, void *data)
{
    return ew_list_insert_after(self, &self->head, data);
}

int ew_list_popback(ew_list *self)
{
    if (!self) {
        return -1;
    }
    return ew_list_delete(self, self->head.prev);
}

int ew_list_popfront(ew_list *self)
{
    if (!self) {
        return -1;
    }
    return ew_list_delete(self, self->head.next);
}

size_t ew_list_size(ew_list *self)
{
    if (!self) {
        return -1;
    }
    return self->size;
}

void *ew_list_front(ew_list *self)
{
    if (!self) {
        return NULL;
    }
    return self->head.next->data;
}

void *ew_list_back(ew_list *self)
{
    if (!self) {
        return NULL;
    }
    return self->head.prev->data;
}

