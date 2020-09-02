#ifndef Z_TEX_H_INCLUDED
#define Z_TEX_H_INCLUDED

struct texpack_st {
    int id;
    char *name;
};

struct texture_st {
    int id;
    char *name;
    int xo, yo;
    int xsz, ysz;
    struct texpack_st *tp;
};

#endif
