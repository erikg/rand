
/*****************************************************************************
 *    rand : write a randomization of files or stdin or parms to stdout
 *    Usage:
 *        blah | rand [-lw] [-o output file]
 *        rand [-lw] -f <file> [-o output file]
 *
 *     Copyright (C) 1998-2010 Erik Greenwald <erik@smluc.org>
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdio.h>

#ifdef ENABLE_NLS
# include <libintl.h>
#endif

#include "help.h"

/** Print version and help info to stdout.
 * @param void This funtion takes no parameters
 * @return This function returns void.
 */
void
show_help ()
{
    fprintf (stdout, gettext ("\
%s %s (C) 1998-2010 Erik Greenwald <erik@smluc.org>\n\
%s comes with ABSOLUTELY NO WARRANTY. Please read the GPL for details.\n\
\n\
Usage:\n\
\t<command> | %s [-lw] [-o <output file>]\n\
\t%s [-lwvh] [-f <input file>] [-o <output file>] [-s <seed>]\n\
\n\
"), PACKAGE, VERSION, PACKAGE, PACKAGE, PACKAGE);
    fprintf (stdout,
	gettext
	(" -l\t\tDisplay lines in random order\n -w\t\tDisplay words in random order\n\n"));
}


/**
 * Print the version to stdout.
 * @param void This funtion takes no parameters
 * @return This function returns void.
 */
void
show_version ()
{
    fprintf (stdout,
	gettext
	("%s %s (C) 1998-2010 Erik Greenwald <erik@smluc.org>\n"),
	PACKAGE, VERSION);
}
