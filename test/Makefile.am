# $Id: Makefile.am,v 1.6 2004/04/11 17:45:17 erik Exp $
#

TESTS=test_rand
noinst_PROGRAMS=test_rand
rand_src = $(top_srcdir)/src/help.c $(top_srcdir)/src/options.c $(top_srcdir)/src/rand.c $(top_srcdir)/src/seed.c
test_rand_SOURCES=test_rand.c test_src_options.c test_src_rand.c test_src_seed.c $(rand_src) $(rand_src:.c=.h)
noinst_HEADERS=test_src_options.h test_src_rand.h test_src_seed.h

AM_CFLAGS = @CHECK_CFLAGS@ @COVERAGE_CFLAGS@
LDADD  = @CHECK_LIBS@ @INTLLIBS@

test: test_rand
	./test_rand

clean-local:
	rm -f *.bb *.bbg *.da test.log

