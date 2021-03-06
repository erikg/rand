########################################################################
# rand                                                                 #
# Copyright (C) 1998-2017 Erik Greenwald <erik@elfga.com>              #
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

AC_INIT([rand], [1.10])
AC_CONFIG_SRCDIR([src/rand.c])
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE

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

AC_CHECK_HEADERS(check.h fcntl.h strings.h sys/stat.h time.h unistd.h)
AC_CHECK_FUNCS([drand48 fchmod fgets fprintf fscanf geteuid \
	getopt getuid memcpy rand sprintf srand48 strlen])

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
