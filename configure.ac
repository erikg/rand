dnl $Id: configure.ac,v 1.8 2005/10/07 15:25:19 erik Exp $

AC_INIT
AC_CONFIG_SRCDIR([src/rand.c])
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE(rand, 1.8)

AC_PROG_CC
AC_PROG_INSTALL

AC_CHECK_HEADERS(unistd.h stdio.h stdlib.h string.h time.h foo.h foobar.h)

AC_CONFIG_FILES([
	Makefile
	docs/Makefile
	src/Makefile
	rand.spec
	rand.lsm
	docs/doxygen.conf
])
AC_OUTPUT
