
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
 * $Id: rand.c,v 1.17 2004/04/11 17:21:58 erik Exp $
 */

/* NOTE: the method I'm using to get a random number LOOKS ineffecient. But
 * that's on purpose. random number generators tend to make the most 
 * significant bits the most random, and the least significant the least
 * random, to generate the optimal spread across the entire range. When a
 * modulus is used to extract the number inside of the range, it takes the 
 * LEAST significant bits, which are the least random. When a plain old slow
 * division is done, it takes the MOST significant bits. This isn't a serious
 * speed loss because % calls a div opcode anyways.       
 *
 * thanks to Dr Shade shade@csc.smsu.edu for the fast table munging algorithm
 * 
 * thanks to Martin Hinsch mhinsch@informatik.uni-osnabrueck.de for the better
 * srand parms  [ srand(getpid()+time()) instead of srand(getpid()) ]
 *
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#ifdef ENABLE_NLS
# include <libintl.h>
#endif

#include "help.h"
#include "options.h"
#include "rand.h"
#include "seed.h"


#define NOMEM gettext("Abort: could not allocate memory\n")


   /**
    * scramble function, for io_pipes and files (not parm).
    * @param method The method type, as defined in the enum.
    * @return Void Nothing.
    * @author Erik Greenwald <erik@smluc.org>
    * @remarks Thanks to Dr Eric Shade for helping out.
    */
void
scramble (char method, FILE *io_pipes[2])
{
    char *blah = NULL, **table = NULL;
    struct ll *llist = NULL, *ptr = NULL;
    int size = 0, n = 0, x = 0;

    if (method == LINE || method == WORD)
    {
	llist = malloc (sizeof (struct ll));
	if (llist == NULL)
	{
	    printf ("%s", NOMEM);
	    return;
	}

	blah = (char *)malloc (sizeof (char) * 1024);
	if (blah == NULL)
	{
	    printf ("%s", NOMEM);
	    free (llist);
	    return;
	}

	llist->data = NULL;
	ptr = llist;

			   /*** make linked list     ***/
	if (method == LINE)
	{
	    while (fgets (blah, 1024, io_pipes[0]))
	    {
		struct ll *m = malloc (sizeof (struct ll)); /* valgrind thinks this is an 8 byte leak? */

		if (m == NULL)
		{
		    printf ("%s", NOMEM);
		    return;
		}
		m->data = malloc (strlen (blah) * sizeof (char) + 2);
		if (m->data == NULL)
		{
		    printf ("%s", NOMEM);
		    return;
		}
		memcpy (m->data, blah, strlen (blah) * sizeof (char) + 1);
		m->data[strlen (m->data) - 1] = (char)0;
		m->next = NULL;
		ptr->next = m;
		ptr = m;
		size++;
	    }
	}
	if (method == WORD)
	{
	    while (fscanf (io_pipes[0], "%s", blah) != EOF)
	    {
		struct ll *m = malloc (sizeof (struct ll));

		if (m == NULL)
		{
		    printf ("%s", NOMEM);
		    free (blah);
		    return;
		}
		m->data = malloc (strlen (blah) * sizeof (char) + 2);
		if (m->data == NULL)
		{
		    printf ("%s", NOMEM);
		    free (m);
		    free (blah);
		    return;
		}
		memcpy (m->data, blah, strlen (blah) * sizeof (char) + 1);
		m->next = NULL;
		ptr->next = m;
		ptr = m;
		size++;
	    }
	}

	   /*** make table from list ***/

	if (size == 0)
	{
	    free (blah);
	    return;
	}
	table = malloc (size * sizeof (void *));
	if (table == NULL)
	{
	    printf ("%s", NOMEM);
	    free (blah);
	    return;
	}
	ptr = llist->next;
	for (x = 0; x < size; x++)
	{
	    table[x] = ptr->data;
	    ptr = ptr->next;
	}
    }

    /*
     * shuffle it  (thanks to Dr Shade) 
     */
    n = size;

    while (n > 1)
    {
	int d = ((double)rand () / RAND_MAX) * n;
	char *temp = table[d];

	table[d] = table[n - 1];
	table[n - 1] = temp;
	--n;
    }

   /*** print it   ***/

    while (size--)
    {
	fprintf (io_pipes[1], "%s\n", table[size]);
	free (table[size]);
    }

   /*** delete the linked list and clean up ***/

    ptr = llist->next;
    while (ptr)
    {
	free (llist);
	llist = ptr;
	ptr = ptr->next;
    }
    free (blah);
    free (table);
    return;
}
