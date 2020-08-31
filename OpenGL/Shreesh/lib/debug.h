/*
@(#)Program:        Autoworld
@(#)File:           debug.h
@(#)Version:        0.1
@(#)Last changed:   2016/01/26 18:58
@(#)Purpose:        Definitions for the debugging system
@(#)Author:         Sarvottamananda Swami
@(#)Copyright:      (C) SS 2016

The following code was taken from Jonathan Leffler.
*/

#ifndef Z_DEBUG_H_INCLUDED
#define Z_DEBUG_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif				/* HAVE_CONFIG_H */

/*
** Control whether debugging macros are active at compile time.
*/
#undef DBG_ACTIVE
#ifdef DEBUG
#define DBG_ACTIVE 1
#else
#define DBG_ACTIVE 0
#endif				/* DEBUG */

/*
** Usage:  DB_TRACE(level, fmt, ...);
**
** The structure of the macros means that the code is always validated
** but is not called when DEBUG is undefined.
** -- See chapter 8 of 'The Practice of Programming', by Kernighan and Pike.
*/
#define DBG_TRACE(level, ...)\
            do { if (DBG_ACTIVE) dbg_print(level, __FILE__, __LINE__,  __VA_ARGS__); } while (0)

/*
** Usage:  DB_CALL(level, ...);
**
** Example: DB_CALL(1, dump_structure(dbg_getfilep(), "tag", arg1, arg2));
**
** If trace is active at given level, execute the code in the variable
** arguments.  Normally used to selectively execute printing functions.
*/
#define DBG_CALL(level, ...)\
            do { if (DBG_ACTIVE && dbg_getdebug() >= (level)) { __VA_ARGS__; } } while (0)

#include <stdio.h>

extern void dbg_init(void);

extern int dbg_getdebug(void);
extern int dbg_setdebug(int level);
extern int dbg_getindent(void);
extern int dbg_setindent(int i);
extern int dbg_newindent(void);
extern int dbg_oldindent(void);
extern void dbg_print(int level, const char *fn, int lno, const char *fmt,
		      ...);
extern FILE *dbg_getfilep(void);
extern FILE *dbg_setfilep(FILE * fp);

extern const char *dbg_getsuffix(void);
extern const char *dbg_setsuffix(const char *s);

/**************************************\
** MULTIPLE DEBUGGING SUBSYSTEMS CODE **
\**************************************/

/*
** Usage:  DBG_MTRACE(subsys, level, fmt, ...);
**
** "subsys" is the debugging system to which this statement belongs.
** The significance of the subsystems is determined by the programmer,
** except that the functions such as dbg_print refer to subsystem 0.
** "level" is the debugging level which must be operational for the
** output to appear. "fmt" is a printf format string. "..." is
** whatever extra arguments fmt requires (possibly nothing).
*/
#define DBG_MTRACE(subsys, level, ...) \
            do { if (DBG_ACTIVE) dbg_mprint(subsys, level, __FILE__, __LINE__, __VA_ARGS__); } while (0)

/*
** Usage:  DBG_MCALL(subsys, level, ...);
**
** Example: DBG_MCALL(subsys, 1, dump_structure(dbg_getfilep(), "tag", arg1, arg2));
**
** If trace is active at given level for given subsystem, execute the
** code in the variable arguments.  Normally used to selectively execute
** printing functions.
*/
#define DBG_MCALL(subsys, level, ...) \
            do { if (DBG_ACTIVE && dbg_mgetdebug(subsys) >= (level)) { __VA_ARGS__; } } while (0)

extern int dbg_mgetdebug(int subsys);
extern int dbg_msetdebug(int subsys, int level);
extern void dbg_mprint(int subsys, int level, const char *fn, int lno,
		       const char *fmt, ...);
extern void dbg_msetsubsysnames(char *const *names);
extern char *dbg_mgetsubsysname(int subsys);
extern void dbg_parsearg(char *arg);

#endif				/* DEBUG_H */
