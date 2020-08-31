#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define	DEBUG
#include "debug.h"

#define MAXSUBSYS	16

static int dbg_level = 0;

static FILE *dbg_filep = NULL;

static int dbg_mlevel[MAXSUBSYS];
char * const * dbg_msubsysname;

#define BOUND(subsys)	((subsys) < 0 ? 0 : ( (subsys) >= MAXSUBSYS ? 0 : (subsys)))

void 
dbg_init(void)
{
	dbg_filep = stderr;

	for (int i = 0 ; i < MAXSUBSYS ; i++){
		dbg_mlevel[i] = 0;
	}
}

int 
dbg_getdebug(void)
{
	return dbg_level;
}

int 
dbg_setdebug(int level)
{
	int oldlevel = dbg_level;

	dbg_level = level;

	if (level > 0)
		fprintf(dbg_filep, "debug level is set to %d\n", level);

	return oldlevel;
}

static int dbg_indent = 4;
static int cur_indent = 0;

int 
dbg_getindent(void)
{
	return dbg_indent;
}

int 
dbg_setindent(int i)
{
	int oldi = dbg_indent;

	dbg_indent = i;
	return oldi;
}

int 
dbg_newindent(void)
{
	int old_indent = cur_indent;

	cur_indent += dbg_indent;
	return old_indent;
}

int 
dbg_oldindent(void)
{
	int old_indent = cur_indent;

	cur_indent -= dbg_indent;
	return old_indent;
}


FILE * 
dbg_getfilep(void)
{
	return dbg_filep;
}

FILE * 
dbg_setfilep(FILE *fp)
{
	FILE * oldfp = dbg_filep;

	dbg_filep = fp;
	return oldfp;
}

const char * dbg_suffix = "Debug";

const char * 
dbg_getsuffix(void)
{
	return dbg_suffix;
}

const char * 
dbg_setsuffix(const char *s)
{
	const char * olds = dbg_suffix;
	dbg_suffix = s;
	return olds;
}

void 
dbg_print(int level, const char *fn, int lno, const char *fmt, ...)
{
	if (dbg_level >= level) {
		va_list ap;

		va_start(ap,fmt);
		fprintf(dbg_filep,"%s:%s:L%d:%*s",dbg_suffix,fn,lno,cur_indent," ");
		vfprintf(dbg_filep,fmt,ap);
		fputc('\n',dbg_filep);
		va_end(ap);
	}
}

int 
dbg_mgetdebug(int subsys)
{
	return dbg_mlevel[BOUND(subsys)];
}

int 
dbg_msetdebug(int subsys, int level)
{
	if (( subsys >= 0 ) && ( subsys < MAXSUBSYS ))
	{
		int oldlevel = dbg_mlevel[subsys];
		dbg_mlevel[subsys] = level;
		return oldlevel;
	}
	return -1;
}

void 
dbg_mprint(int subsys, int level, const char *fn, int lno, const char * fmt, ... )
{
	subsys = BOUND(subsys);

	if (dbg_mlevel[subsys] >= level) {
		va_list ap;

		va_start(ap,fmt);
		fprintf(dbg_filep,"%s:%s:%s:L%d:%*s",dbg_suffix,dbg_msubsysname[subsys],fn,lno,cur_indent," ");
		vfprintf(dbg_filep,fmt,ap);
		fputc('\n',dbg_filep);
		va_end(ap);
	}
}

void 
dbg_msetsubsysnames(char * const * names)
{
	dbg_msubsysname = names;
}

char * 
dbg_mgetsubsysname(int subsys)
{
	subsys = BOUND(subsys);

	return dbg_msubsysname[subsys];
}

void
dbg_parsearg(char *arg)
{
	char * s;
	char * saveptr1;
	char * saveptr2;

	s = strtok_r(arg, ",", &saveptr1);
	while (s!=NULL){
		char * tok;
		tok = strtok_r(s, ":", &saveptr2);

		int i = 0;
		while (dbg_msubsysname[i]!=NULL){
			if (strcmp(dbg_msubsysname[i],tok) == 0){
				char * subtok;
				subtok = strtok_r(NULL, ",:", &saveptr2);
				dbg_mlevel[i] = atoi(subtok);

				fprintf(dbg_filep, "debug level is set to %d for subsys %s\n", 
						dbg_mlevel[i], dbg_msubsysname[i]);

				break;
			}
			i++;
		};

		s = strtok_r(NULL, ",", &saveptr1);
	}
}
