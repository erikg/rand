bin_PROGRAMS = rand
rand_SOURCES = rand.c
rand_LDADD   = @INTLLIBS@ 
localedir    = $(datadir)/locale
INCLUDES     = -I../intl -I$(toplevel_dir)/intl -DLOCALEDIR=\"$(localedir)\"

lint:
	lclint $(CFLAGS) +posixstrictlib rand.c > rand.c.lint
indent:
	indent rand.c

