#ifndef A_DEFS_H_INCLUDED
#define A_DEFS_H_INCLUDED

#ifdef DEBUG
enum debug_t {
    D_ALL = 0, D_FATAL = 1, D_ERROR = 2, D_WARNING = 3,
    D_INFO = 4, D_DEBUG = 5, D_FUNCS = 6, D_PARAMS = 7,
    D_DUMP = 8
};
#endif

#endif
