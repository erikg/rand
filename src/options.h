
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
 * $Id: options.h,v 1.6 2004/02/17 00:20:53 erik Exp $
 */

#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdio.h>

enum {
    LINE,
    WORD,
    ERR
};

unsigned char options (int argc, char **argv, FILE *io_pipes[2]);

#endif
