#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "a-defs.h"
//#include <assert.h>

//#include "a-globals.h"
//#include "z-debug.h"
#include "z-options.h"

void process_options(int argc, char **argv, struct options_st *opt)
{
    int c;

    while (1) {
	struct option long_options[] = {
	    /* These options set a flag. */
	    {"verbose", no_argument, &(opt->verbose), 1},
	    {"brief", no_argument, &(opt->verbose), 0},
	    /* These options don’t set a flag.
	     * We distinguish them by their indices. */
	    {"fullscreen", no_argument, &(opt->fullscreen), 1},
	    {"windowed", no_argument, &(opt->fullscreen), 0},
	    {"width", required_argument, 0, 'w'},
	    {"height", required_argument, 0, 'h'},
#ifdef DEBUG
	    {"debug", required_argument, 0, 'd'},
	    {"mdebug", required_argument, 0, 0},
#endif
	    {0, 0, 0, 0}
	};
	/* getopt_long stores the option index here. */
	int option_index = 0;

#ifdef DEBUG
	c = getopt_long(argc, argv, "vw:h:d:", long_options, &option_index);
#else
	c = getopt_long(argc, argv, "vw:h:", long_options, &option_index);
#endif

	/* Detect the end of the options. */
	if (c == -1)
	    break;

	switch (c) {
	case 0:
	    /*
	       printf("option %s", long_options[option_index].name);
	       if (optarg)
	       printf(" with arg %s", optarg);
	       printf("\n");
	     */
#ifdef DEBUG
	    if (strcmp(long_options[option_index].name, "mdebug") == 0) {
		opt->mdebug = strdup(optarg);
	    }
#endif

	    break;

	case 'v':
	    /*
	       puts("option -v");
	     */
	    break;

	case 'w':
	    /*
	       printf("option -w with value `%s'\n", optarg);
	     */
	    opt->width = atoi(optarg);
	    break;

	case 'h':
	    /*
	       printf("option -h with value `%s'\n", optarg);
	     */
	    opt->height = atoi(optarg);
	    break;

#ifdef DEBUG
	case 'd':
	    /*
	       printf("option -d with value `%s'\n", optarg);
	     */
	    opt->debug = atoi(optarg);
	    break;
#endif
	case '?':
	    /* getopt_long already printed an error message. */
	    break;

	default:
	    abort();
	}
    }

    /*
       if (opt->verbose)
       puts("verbose flag is set");

       if (opt->fullscreen)
       puts("fullscreen flag is set");
     */

#ifdef DEBUG
    /* Report debug value */
    /*
       if (opt->debug)
       printf("debugging is set with level %d\n", opt->debug);

       if (opt->mdebug)
       printf("debugging systems is  set to %s\n", opt->mdebug);
     */
#endif

    /* Print any remaining command line arguments (not options). */
    if (optind < argc) {
	fprintf(stderr, "non-option ARGV-elements: ");
	while (optind < argc)
	    fprintf(stderr, "%s ", argv[optind++]);
	fputc('\n', stderr);
    }
}
