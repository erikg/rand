# $Id: Makefile.am,v 1.2 2004/02/18 01:32:59 erik Exp $
#

TESTS=test_rand
noinst_PROGRAMS=test_rand
rand_src = $(top_srcdir)/src/help.c $(top_srcdir)/src/options.c $(top_srcdir)/src/rand.c $(top_srcdir)/src/seed.c
test_rand_SOURCES=test_rand.c test_src_options.c $(rand_src) $(rand_src:.c=.h)
noinst_HEADERS=test_src_options.h

test_rand_CFLAGS = @CHECK_CFLAGS@
test_rand_LDADD  = @CHECK_LIBS@

test: test_rand
	./test_rand
