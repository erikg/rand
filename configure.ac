dnl $Id: configure.ac,v 1.7 2005/03/15 13:00:48 erik Exp $

AC_INIT
AC_CONFIG_SRCDIR([src/rand.c])
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE(rand, 1.8)

dnl these /usr/local and /sw (fink) path checks were snarfed from 
dnl brlcad, http://brlcad.sourceforge.net

dnl autosearch /usr/local
AC_MSG_CHECKING([for /usr/local])
if test -d /usr/local/include ; then
	AC_MSG_RESULT([found, adding /usr/local to search paths])
	CPPFLAGS="$CPPFLAGS -I/usr/local/include"
	if test -d /usr/local/lib ; then
		LDFLAGS="$LDFLAGS -L/usr/local/lib"
	fi
else
	AC_MSG_RESULT([not found])
fi

dnl autosearch fink paths
AC_MSG_CHECKING([for fink in /sw])
if test -d /sw/include ; then
	AC_MSG_RESULT([found, adding /sw to search paths])
	CPPFLAGS="$CPPFLAGS -I/sw/include"
	if test -d /sw/lib ; then
		LDFLAGS="$LDFLAGS -L/sw/lib"
	fi
else
	AC_MSG_RESULT([not found])
fi

dnl end of seans brlcad stuff

ALL_LINGUAS="en en_AU en_CA en_GB en_IE en_US pt pt_BR"
#AM_GNU_GETTEXT([external])
if test "$USE_NLS" != "yes" 
then
	AC_DEFINE(gettext,,No gettext)
fi

AC_PROG_CC
AC_PROG_INSTALL

AC_CHECK_HEADERS(unistd.h stdio.h stdlib.h string.h time.h)

#COVERAGE_CFLAGS="-fprofile-arcs -ftest-coverage"
#AM_PATH_CHECK(,have_test=yes,have_test=no)
#AM_CONDITIONAL(TEST, [test x"$have_test" = xyes])
#AC_SUBST(CHECK_CFLAGS)
#AC_SUBST(CHECK_LIBS)
#AC_SUBST(COVERAGE_CFLAGS)

#AC_CONFIG_FILES([Makefile po/Makefile.in docs/Makefile src/Makefile test/Makefile rand.spec rand.lsm docs/doxygen.conf])
AC_CONFIG_FILES([
	Makefile
	docs/Makefile
	src/Makefile
	rand.spec
	rand.lsm
	docs/doxygen.conf
])
AC_OUTPUT
