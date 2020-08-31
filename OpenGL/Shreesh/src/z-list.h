#ifndef Z_LIST_H_INCLUDED
#define Z_LIST_H_INCLUDED

struct dlist_st {
    void *data;
    struct dlist_st *next;
    struct dlist_st *prev;
};

struct dlist_hdr {
    struct dlist_st *first;
    struct dlist_st *last;
    int size;
};

extern struct dlist_hdr *dl_create(void);
extern void dl_destroy(struct dlist_hdr **);
extern void dl_insert(struct dlist_hdr *, void *);
extern void dl_delete(struct dlist_hdr *, struct dlist_st *);
extern struct dlist_st *dl_search(struct dlist_hdr *, void *);
extern void dl_search_and_insert(struct dlist_hdr *, void *);

struct list_st {
    void *data;
    struct list_st *next;
};

extern struct list_st *sl_create(void);
extern void sl_destroy(struct list_st **);
extern struct list_st *sl_push(struct list_st *, void *);
extern struct list_st *sl_pop(struct list_st *, void **);
extern struct list_st *sl_search(struct list_st *, void *);

struct listi_st {
    int data;
    struct listi_st *next;
};

extern struct listi_st *sli_create(void);
extern void sli_destroy(struct listi_st **);
extern struct listi_st *sli_push(struct listi_st *, int);
extern struct listi_st *sli_pop(struct listi_st *, int *);
extern struct listi_st *sli_search(struct listi_st *, int);

#endif
