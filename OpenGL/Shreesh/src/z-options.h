#ifndef Z_OPTIONS_H_INCLUDED
#define Z_OPTIONS_H_INCLUDED

struct options_st {
    int width;
    int height;
    int fullscreen;
    int debug;
    char *mdebug;
    int verbose;
};

extern void process_options(int, char **, struct options_st *);

#endif
