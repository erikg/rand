# $Id: Makefile.am,v 1.10 2004/07/05 14:09:51 erik Exp $

bin_PROGRAMS = rand
rand_SOURCES = main.c rand.c seed.c help.c options.c
rand_LDADD   = @INTLLIBS@ 

noinst_HEADERS = rand.h seed.h help.h options.h

localedir    = $(datadir)/locale
INCLUDES     = -DLOCALEDIR=\"$(localedir)\"

lint:
	for a in ${rand_SOURCES} ${noinst_HEADERS} ; do splint $(CFLAGS) +posixstrictlib $$a > $$a.lint ; done
indent:
	indent rand.c

gindent:
	gindent ${rand_SOURCES} ${noinst_HEADERS}

grind: rand
	/bin/ls | valgrind --leak-check=yes -v --show-reachable=yes --track-fds=yes --gdb-attach=yes ./rand 2> ../dump
