#include <stdlib.h>

#include "z-list.h"

struct dlist_hdr *dl_create(void)
{
    struct dlist_hdr *tmp = NULL;

    tmp = (struct dlist_hdr *)malloc(sizeof(struct dlist_hdr));
    tmp->size = 0;
    tmp->first = NULL;
    tmp->last = NULL;

    return tmp;
}

void dl_insert(struct dlist_hdr *dl, void *p)
{
    struct dlist_st *tmp;

    tmp = (struct dlist_st *)malloc(sizeof(struct dlist_st));
    tmp->data = p;

    if (dl->last == NULL) {
	tmp->next = NULL;
	tmp->prev = NULL;
	dl->first = tmp;
	dl->last = tmp;
    } else {
	tmp->prev = dl->last;
	tmp->next = NULL;
	dl->last->next = tmp;
	dl->last = tmp;
    }
    dl->size++;
}

void dl_search_and_insert(struct dlist_hdr *dl, void *p)
{
    if (dl_search(dl, p) == NULL) {
	dl_insert(dl, p);
    }
}

void dl_delete(struct dlist_hdr *dl, struct dlist_st *p)
{
    if (p == NULL)
	return;

    if (dl->size == 1) {
	dl->first = NULL;
	dl->last = NULL;
    } else {
	if (p->next == NULL) {
	    dl->last = p->prev;
	    dl->last->next = NULL;
	} else if (p->prev == NULL) {
	    dl->first = p->next;
	    dl->first->prev = NULL;
	} else {
	    p->next->prev = p->prev;
	    p->prev->next = p->next;
	}
    }

    free(p);

    dl->size--;
}

struct dlist_st *dl_search(struct dlist_hdr *dl, void *p)
{
    struct dlist_st *t = NULL;

    t = dl->first;

    while (t != NULL) {
	if (t->data == p)
	    return t;
	t = t->next;
    }
    return NULL;
}

void dl_destroy(struct dlist_hdr **dl)
{
    struct dlist_st *t;
    struct dlist_st *tmp;

    t = (*dl)->first;
    while (t != NULL) {
	tmp = t;
	t = t->next;
	free(tmp);
    }
    *dl = NULL;

    free(dl);
}

struct list_st *sl_create(void)
{
    return NULL;
}

void sl_destroy(struct list_st **l)
{
    struct list_st *t;
    struct list_st *tmp;

    t = *l;
    while (t != NULL) {
	tmp = t;
	t = t->next;
	free(tmp);
    }
    *l = NULL;
}

struct list_st *sl_push(struct list_st *l, void *p)
{
    struct list_st *tmp;

    tmp = (struct list_st *)malloc(sizeof(struct list_st));
    tmp->data = p;
    tmp->next = l;
    return l;
}

struct list_st *sl_pop(struct list_st *l, void **p)
{
    struct list_st *tmp;

    tmp = l;
    l = l->next;
    *p = tmp->data;
    free(tmp);
    return l;

}

struct list_st *sl_search(struct list_st *l, void *p)
{
    struct list_st *t = NULL;

    t = l;

    while (t != NULL) {
	if (t->data == p)
	    return t;
	t = t->next;
    }
    return NULL;
}

struct listi_st *sli_create(void)
{
    return NULL;
}

void sli_destroy(struct listi_st **l)
{
    struct listi_st *t;
    struct listi_st *tmp;

    t = *l;
    while (t != NULL) {
	tmp = t;
	t = t->next;
	free(tmp);
    }
    *l = NULL;
}

struct listi_st *sli_push(struct listi_st *l, int n)
{
    struct listi_st *tmp;

    tmp = (struct listi_st *)malloc(sizeof(struct listi_st));
    tmp->data = n;
    tmp->next = l;
    return l;
}

struct listi_st *sli_pop(struct listi_st *l, int *pn)
{
    struct listi_st *tmp;

    tmp = l;
    l = l->next;
    *pn = tmp->data;
    free(tmp);
    return l;

}

struct listi_st *sli_search(struct listi_st *l, int n)
{
    struct listi_st *t = NULL;

    t = l;

    while (t != NULL) {
	if (t->data == n)
	    return t;
	t = t->next;
    }
    return NULL;
}
