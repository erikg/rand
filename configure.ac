########################################################################
# rand                                                                 #
# Copyright (C) 1998-2007 Erik Greenwald <erik@smluc.org>              #
#                                                                      #
# This program is free software; you can redistribute it and/or modify #
# it under the terms of the GNU General Public License as published by #
# the Free Software Foundation; either version 2 of the License, or    #
# (at your option) any later version.                                  #
#                                                                      #
# This program is distributed in the hope that it will be useful,      #
# but WITHOUT ANY WARRANTY; without even the implied warranty of       #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        #
# GNU General Public License for more details.                         #
#                                                                      #
# You should have received a copy of the GNU General Public License    #
# along with this program; if not, write to the Free Software          #
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.            #
#                                                                      #
########################################################################

# $Id: configure.ac,v 1.15 2007/11/20 16:33:24 erik Exp $

AC_INIT
AC_CONFIG_SRCDIR([src/rand.c])
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE(rand, 1.9)

AC_DEFUN([SEARCH],[DIR="$1"
AC_MSG_CHECKING([for $DIR])
if test -d $DIR/include ; then
	AC_MSG_RESULT([found, adding $DIR to search paths])
	CPPFLAGS="$CPPFLAGS -I$DIR/include"
	if test -d $DIR/lib ; then LDFLAGS="$LDFLAGS -L$DIR/lib"; fi
else AC_MSG_RESULT([not found]); fi ])

SEARCH(/usr/local)
SEARCH(/opt/local)
SEARCH(/sw)

AC_PROG_CC
AC_PROG_INSTALL

ALL_LINGUAS="en en_AU en_CA en_GB en_IE en_US pt pt_BR"
AM_GNU_GETTEXT([external])
if test "$USE_NLS" = "no"
then
	AC_DEFINE(gettext,,No gettext)
fi

AC_CHECK_HEADERS(check.h fcntl.h stdio.h stdlib.h string.h sys/stat.h time.h unistd.h)
AC_CHECK_FUNCS([atoi drand48 fchmod fclose fgets fopen fprintf free fscanf geteuid \
	getopt getuid malloc memcpy printf rand sprintf srand48 strlen])

AC_CONFIG_FILES([
	Makefile
	debian/Makefile
	docs/Makefile
	docs/doxygen.conf
	m4/Makefile
	po/Makefile.in
	rand.lsm
	rand.spec
	src/Makefile
])
AC_OUTPUT
