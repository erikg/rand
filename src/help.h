
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
 * $Id: help.h,v 1.7 2007/11/20 00:28:10 erik Exp $
 */

#ifndef HELP_H
#define HELP_H

void show_help ();
void show_version ();

#endif
