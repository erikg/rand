dnl $Id: configure.ac,v 1.9 2007/11/19 22:26:44 erik Exp $

AC_INIT
AC_CONFIG_SRCDIR([src/rand.c])
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE(rand, 1.8)

AC_PROG_CC
AC_PROG_INSTALL

ALL_LINGUAS="en en_AU en_CA en_GB en_IE en_US pt pt_BR"
AM_GNU_GETTEXT([external])
if test "$USE_NLS" = "no"
then
	AC_DEFINE(gettext,,No gettext)
fi

AC_CHECK_HEADERS(unistd.h stdio.h stdlib.h string.h time.h foo.h foobar.h)

AC_CONFIG_FILES([ 
	Makefile
	docs/Makefile
	docs/doxygen.conf
	po/Makefile.in
	rand.lsm
	rand.spec
	src/Makefile
])
AC_OUTPUT
