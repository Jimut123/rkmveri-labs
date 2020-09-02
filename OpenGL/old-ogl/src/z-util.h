#ifndef Z_UTIL_H_INCLUDED
#define Z_UTIL_H_INCLUDED

extern int getverbosity(void);
extern int setverbosity(int);

extern void printf_verbose(const char *fmt, ...);
extern void printf_terse(const char *fmt, ...);
#endif
