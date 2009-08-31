
/*****************************************************************************
 *    rand : write a randomization of files or stdin or parms to stdout
 *    Usage:
 *        blah | rand [-lw] [-o output file]
 *        rand [-lw] -f <file> [-o output file]
 *
 *     Copyright (C) 1998-2009 Erik Greenwald <erik@smluc.org>
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
 * $Id: seed.c,v 1.14 2009/08/31 17:40:38 erik Exp $
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "seed.h"

#if HAVE_GETEUID
# define GETUID geteuid()
#elif HAVE_GETUID
# define GETUID getuid()
#else
# define GETUID 0
#endif

/*
 * Write out the random seed. This is done on each pass per euid, so if an
 * effective user wants to recover the last random seed, there is a place to
 * extract it from.
 * @param void No parameters accepted.
 * @return Void. Nothing returned.
 */
void
seed_rand ()
{
    unsigned int seed;
    FILE *f;
    char s[1024];

    /*
     * seed the entropy pool from here, so we can override it
     *
     * thanks to Martin Hinsch for the +time(0)
     */
    seed = ((unsigned int)(getpid () * time (NULL)));
#ifdef HAVE_DRAND48
    srand48 (seed);
#else
    srand (seed);
#endif
    sprintf (s, "/var/tmp/rand.%d", GETUID);
    if((f = fopen (s, "w")) == NULL)
	    return;
    fprintf (f, "%u\n", seed);
    fclose (f);
    return;
}

/**
 * I have no clue why this is here.
 */
void
old_seed ()
{
    unsigned int seed;
    FILE *f;
    char s[1024];

    sprintf (s, "/var/tmp/rand.%d", GETUID);
    if( (f = fopen (s, "r")) == NULL)
	    return;
    fscanf (f, "%u\n", &seed);
    fclose (f);
#ifdef HAVE_DRAND48
    srand48 (seed);
#else
    srand (seed);
#endif
    return;
}

/**
 * Seed a random number.
 * @param arg eh?
 * @return Void... Nothing returned.
 */
void
seed (char *arg)
{
    if (arg == NULL)
	seed_rand ();
    else if (arg[0] == '.')
	old_seed ();
    else
	srand (atoi (arg));
    return;
}
