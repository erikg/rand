
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
 * $Id: seed.c,v 1.4 2004/02/16 14:31:07 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "seed.h"

void
seed_rand ()
{
    unsigned int seed;
    FILE *f;
    char s[1024];

    /*
     * seed the entropy pool from here, so we can override it 
     */
    /*
     * thanks to Martin Hinsch for the +time(0) 
     */
    seed = ((unsigned int)(getpid () + time (NULL)));
    srand (seed);
    sprintf (s, "/var/tmp/rand.%d", geteuid ());
    f = fopen (s, "w");
    fprintf (f, "%u\n", seed);
    fclose (f);
    return;
}

old_seed ()
{
    unsigned int seed;
    FILE *f;
    char s[1024];

    sprintf (s, "/var/tmp/rand.%d", geteuid ());
    f = fopen (s, "r");
    fscanf (f, "%u\n", &seed);
    fclose (f);
    srand (seed);
    return;
}

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
