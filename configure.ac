dnl $Id: configure.ac,v 1.3 2004/04/11 17:22:09 erik Exp $

AC_INIT
AC_CONFIG_SRCDIR([src/rand.c])
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE(rand, 1.8)

ALL_LINGUAS="en en_AU en_CA en_GB en_IE en_US pt pt_BR"
AM_GNU_GETTEXT(external, need-ngettext)
if test "$USE_NLS" = "no" 
then
	AC_DEFINE(gettext,,No gettext)
fi

AC_PROG_CC
AC_PROG_INSTALL

AC_CHECK_HEADERS(unistd.h stdio.h stdlib.h string.h time.h)

COVERAGE_CFLAGS="-fprofile-arcs -ftest-coverage"
AM_PATH_CHECK(,have_test=yes,have_test=no)
AM_CONDITIONAL(TEST, [test x"$have_test" = xyes])
AC_SUBST(CHECK_CFLAGS)
AC_SUBST(CHECK_LIBS)
AC_SUBST(COVERAGE_CFLAGS)

AC_CONFIG_FILES([Makefile po/Makefile.in docs/Makefile src/Makefile test/Makefile rand.spec rand.lsm docs/doxygen.conf])
AC_OUTPUT
