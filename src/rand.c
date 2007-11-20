
/*****************************************************************************
 *    rand : write a randomization of files or stdin or parms to stdout
 *    Usage:
 *        blah | rand [-lw] [-o output file]
 *        rand [-lw] -f <file> [-o output file]
 *
 *     Copyright (C) 1998-2007 Erik Greenwald <erik@smluc.org>
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
 * $Id: rand.c,v 1.26 2007/11/20 19:38:10 erik Exp $
 */

/* 
 * NOTE: the method I'm using to get a random number LOOKS ineffecient. But
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

static int
shuffle (char **table, int size)
{
    int n = size;

    while (n > 1)
    {
#ifdef HAVE_DRAND48
	int d = drand48 () * n;
#else
	int d = ((double)rand () / RAND_MAX) * n;
#endif
	char *temp = table[d];

	table[d] = table[n - 1];
	table[n - 1] = temp;
	--n;
    }
    return 0;
}

static struct ll *
readlines (FILE * io_pipes[2], int *size)
{
    char blah[BUFSIZ];
    struct ll *head = NULL, *last = NULL;

    while (fgets (blah, BUFSIZ, io_pipes[0]))
    {
	struct ll *m = malloc (sizeof (struct ll));

	if (head == NULL)
	    head = m;
	else
	    last->next = m;
	last = m;

	if (m == NULL)
	{
	    printf ("%s", NOMEM);
	    return NULL;
	}
	m->data = strdup (blah);
	if (m->data == NULL)
	{
	    printf ("%s", NOMEM);
	    free (m);
	    return NULL;
	}
	m->next = NULL;
	size[0]++;
    }
    return head;
}

static struct ll *
readwords (FILE * io_pipes[2], int *size)
{
    char blah[BUFSIZ], fmt[16];
    struct ll *head = NULL, *last = NULL;

    blah[BUFSIZ-1] = '\0';
    snprintf(fmt, 16, "%%%ds", BUFSIZ);
    while (fscanf (io_pipes[0], fmt, blah) != EOF)
    {
	int len;
	struct ll *m = malloc (sizeof (struct ll));

	if (head == NULL)
	    head = m;
	else
	    last->next = m;
	last = m;

	if (m == NULL)
	{
	    printf ("%s", NOMEM);
	    return NULL;
	}

	len = strlen (blah);
	m->data = malloc (len * sizeof (char) + 2);
	if (m->data == NULL)
	{
	    printf ("%s", NOMEM);
	    free (m);
	    return NULL;
	}
	memcpy (m->data, blah, len * sizeof (char));
	m->data[len] = '\n';
	m->data[len + 1] = '\0';
	m->next = NULL;
	size[0]++;
    }
    return head;
}

static int
freelist (struct ll *llist)
{
    struct ll *ptr = llist;

    while (ptr)
    {
	ptr = llist->next;
	free (llist);
	llist = ptr;
    }
    return 0;
}

static int
list_to_table (struct ll *ptr, char **table, int size)
{
    int x;

    for (x = 0; x < size; x++)
    {
	table[x] = ptr->data;
	ptr = ptr->next;
    }
    return 0;
}

static int
printtable (char **table, int size, FILE * out)
{
    while (size--)
	fprintf (out, "%s", table[size]);
    return 0;
}

static int
freetable (char **table, int size)
{
    while (size--)
	free (table[size]);
    return 0;
}

   /**
    * scramble function, for io_pipes and files (not parm).
    * @param method The method type, as defined in the enum.
    * @return Void Nothing.
    * @author Erik Greenwald <erik@smluc.org>
    * @remarks Thanks to Dr Eric Shade for helping out.
    */
void
scramble (char method, FILE * io_pipes[2])
{
    char **table = NULL;
    int size = 0;

    if (method == LINE || method == WORD)
    {
	struct ll *ptr = NULL;

	   /*** make linked list     ***/
	if (method == LINE)
	    ptr = readlines (io_pipes, &size);
	if (method == WORD)
	    ptr = readwords (io_pipes, &size);

	   /*** make table from list ***/

	if (size == 0)
	    return;

	table = malloc (size * sizeof (void *));
	if (table == NULL)
	{
	    printf ("%s", NOMEM);
	    return;
	}

	list_to_table (ptr, table, size);

	   /*** delete the linked list and clean up ***/
	freelist (ptr);
    }

    /*
     * shuffle it  (thanks to Dr Shade)
     */
    shuffle (table, size);

   /*** print it   ***/

    printtable (table, size, io_pipes[1]);

    freetable (table, size);
    free (table);
    return;
}
