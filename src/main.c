
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
 * $Id: main.c,v 1.4 2004/02/16 14:31:07 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>

#ifdef HAVE_GETTEXT
# include <locale.h>
# include <libintl.h>
#endif

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "help.h"
#include "seed.h"
#include "rand.h"
#include "options.h"

int
main (int argc, char **argv)
{
#ifdef HAVE_GETTEXT
    setlocale (LC_ALL, "");
    bindtextdomain (PACKAGE, LOCALEDIR);
    textdomain (PACKAGE);
#endif

    seed (NULL);

    scramble (options (argc, argv));

    return EXIT_SUCCESS;
}
