/*****************************************************************************
 *    rand.c : write a randomization of files or stdin or parms to stdout
 *    Usage:
 *        blah | rand [-lw] [-o output file]
 *        rand [-lw] -f <file> [-o output file]
 *        rand <parms to be randomized>      <-- not anymore.
 * 	
 *     Copyright (C) 1998-2001 Erik Greenwald <erik@smluc.org>
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <libintl.h>

#ifndef _
#define _(String) gettext(String)
#endif

#define LINE 'l'
#define WORD 'w'
#define ERR 255

#define NOMEM _("Abort: could not allocate memory\n")

   /*** struct for the linked lists ***/
struct ll
{
  char *data;
  struct ll *next;
};

   /*** scramble function, for pipe and files (not parm) ***/

static void
scramble (FILE * fp, FILE * fo, char method)
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

      blah = (char *) malloc (sizeof (char) * 1024);
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
	  while (fgets (blah, 1024, fp))
	    {
	      struct ll *m = malloc (sizeof (struct ll));
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
	      m->data[strlen (m->data) - 1] = (char) 0;
	      m->next = NULL;
	      ptr->next = m;
	      ptr = m;
	      size++;
	    }
	}
      if (method == WORD)
	{
	  while (fscanf (fp, "%s", blah) != EOF)
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

  /* shuffle it  (thanks to Dr Shade) */
  n = size;

  while (n > 1)
    {
      int d = ((double) rand () / RAND_MAX) * n;
      char *temp = table[d];
      table[d] = table[n - 1];
      table[n - 1] = temp;
      --n;
    }

   /*** print it   ***/

  while (size)
    {
      fprintf (fo, "%s\n", table[size - 1]);
      size--;
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

/***********************************************************************/

static void
show_help ()
{
  fprintf (stdout, _("\
%s %s (C) 1998-2001 Erik Greenwald <erik@math.smsu.edu>\n\
%s comes with ABSOLUTELY NO WARRANTY. Please read the GPL for details.\n\
\n\
Usage:\n\
\t<command> | %s [-lw] [-o <output file>]\n\
\t%s [-lwvh] [-f <input file>] [-o <output file>] [-s <seed>]\n\
\n\
"), PACKAGE, VERSION, PACKAGE, PACKAGE, PACKAGE);
  fprintf (stdout,
	   _
	   (" -l\t\tDisplay lines in random order\n -w\t\tDisplay words in random order\n\n"));
}

static void
show_version ()
{
  fprintf (stdout,
	   _
	   ("%s %s (C) 1998-2001 Erik Greenwald <erik@math.smsu.edu>\n"),
	   PACKAGE, VERSION);
}

/***********************************************************************/

int
main (int argc, char **argv)
{
  int c;
  FILE *fp = stdin;
  FILE *fo = stdout;

  char method;

  /* do the gettext shtuff */

  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  /* gettext is ready to roll */

  method = LINE;		/* default to LINE method */

  /* seed the entropy pool from here, so we can override it */
  /* thanks to Martin Hinsch for the +time(0) */
  srand ((unsigned int) (getpid () + time (NULL)));

  while ((c = getopt (argc, argv, "f:hlo:s:vw")) != EOF)
    switch ((char) c)
      {
      case 'f':
	if ((fp = fopen (optarg, "r")) == NULL)
	  {
	    fprintf (stderr, _("Cannot open %s for reading\n"), optarg);
	    return -1;
	  }
	break;
      case 'h':
	show_help ();
	return EXIT_SUCCESS;
      case 'l':
	method = LINE;
	break;
      case 'o':
	if ((fo = fopen (optarg, "w")) == NULL)
	  {
	    fprintf (stderr, _("Cannot open %s for writing\n"), optarg);
	    return EXIT_FAILURE;
	  }
	break;			/*oops, thanks to Tim Clapin for pointing out this ommision */
      case 's':
	srand (atoi (optarg));	/* we're not worried about over/under flow */
	break;
      case 'v':
	show_version ();
	return EXIT_SUCCESS;
      case 'w':
	method = WORD;
	break;
      default:
	show_help ();
	return EXIT_FAILURE;
      }

  scramble (fp, fo, method);

  return 0;
}
