#include <stdarg.h>
#include <stdio.h>

#include "z-util.h"

static int verbose = 0;

int getverbosity(void)
{
    return verbose;
}

int setverbosity(int newvalue)
{
    int oldvalue = verbose;
    verbose = newvalue;
    return oldvalue;
}

void printf_verbose(const char *fmt, ...)
{
    if (verbose) {
	va_list ap;

	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
    }
}

void printf_terse(const char *fmt, ...)
{
    if (!verbose) {
	va_list ap;

	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
    }
}
