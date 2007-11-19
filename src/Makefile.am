# $Id: Makefile.am,v 1.14 2007/11/19 22:24:15 erik Exp $

bin_PROGRAMS = rand
rand_SOURCES = main.c rand.c seed.c help.c options.c

noinst_HEADERS = rand.h seed.h help.h options.h

localedir    = $(datadir)/locale
INCLUDES     = -DLOCALEDIR=\"$(localedir)\"
rand_LDADD=	$(LTLIBINTL)

lint:
	for a in ${rand_SOURCES} ${noinst_HEADERS} ; do splint $(CFLAGS) +posixstrictlib $$a > $$a.lint ; done
indent:
	indent rand.c

gindent:
	gindent ${rand_SOURCES} ${noinst_HEADERS}

grind: rand
	/bin/ls | valgrind --leak-check=yes -v --show-reachable=yes --track-fds=yes --gdb-attach=yes ./rand 2> ../dump
