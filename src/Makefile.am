bin_PROGRAMS = rand
rand_SOURCES = main.c rand.c seed.c help.c options.c
rand_LDADD   = @INTLLIBS@ 

noinst_HEADERS = rand.h seed.h help.h options.h

localedir    = $(datadir)/locale
INCLUDES     = -DLOCALEDIR=\"$(localedir)\"

lint:
	lclint $(CFLAGS) +posixstrictlib rand.c > rand.c.lint
indent:
	indent rand.c

gindent:
	gindent ${rand_SOURCES} ${noinst_HEADERS}
