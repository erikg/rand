
/*****************************************************************************
 *    rand : write a randomization of files or stdin or parms to stdout
 *    Usage:
 *        blah | rand [-lw] [-o output file]
 *        rand [-lw] -f <file> [-o output file]
 * 	
 *     Copyright (C) 1998-2004 Erik Greenwald <erik@smluc.org>
 * 
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program; if not, write to the Free Software
 *     Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 ******************************************************************************/

/*
 * $Id: options.c,v 1.9 2004/02/16 17:25:07 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#ifdef HAVE_GETTEXT
# include <locale.h>
# include <libintl.h>
# ifndef _
#  define _(String) gettext(String)
# endif
#else
# define _(String) String
#endif

#include "help.h"
#include "seed.h"
#include "options.h"

FILE *io_pipes[2];

/**
 * Parse the command line options
 * \param argc The number of arguments.
 * \param argv The arguments as char**.
 * \return The method type.
 * \author Erik Greenwald <erik@smluc.org>
 */
unsigned char
options (int argc, char **argv)
{
    int c;
    unsigned char method = LINE;

    io_pipes[0] = stdin;
    io_pipes[1] = stdout;

    while ((c = getopt (argc, argv, "f:o:lws:hv")) != EOF)
	switch ((char)c)
	{
	case 'f':
	    if ((io_pipes[0] = fopen (optarg, "r")) == NULL)
	    {
		fprintf (stderr, _("Cannot open %s for reading\n"), optarg);
		return EXIT_FAILURE;
	    }
	    break;
	case 'o':
	    if ((io_pipes[1] =
		    fopen (optarg, "w")) == NULL)
	    {
		fprintf (stderr, _("Cannot open %s for writing\n"), optarg);
		return EXIT_FAILURE;
	    }
	    chmod(optarg, 0600);
	    break;		/*oops, thanks to Tim Clapin for pointing out this ommision */
	case 'l':
	    method = LINE;
	    break;
	case 'w':
	    method = WORD;
	    break;
	case 's':
	    seed (optarg);
	    break;
	case 'v':
	    show_version ();
	    exit (EXIT_SUCCESS);
	case 'h':
	    show_help ();
	    exit (EXIT_SUCCESS);
	default:
	    show_help ();
	    exit (EXIT_FAILURE);
	}
    return method;
}
