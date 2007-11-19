# $Id: Makefile.am,v 1.16 2007/11/19 22:26:01 erik Exp $
#

#if TEST
#TEST=test
#endif
TEST=

SUBDIRS = src docs po $(TEST)

EXTRA_DIST= config.rpath config.rpath ChangeLog $(PACKAGE).spec.in \
	rand.lsm.in m4/gettext.m4 m4/iconv.m4 m4/lib-ld.m4 \
	m4/lib-link.m4 m4/lib-prefix.m4 m4/nls.m4 m4/po.m4 \
	m4/progtest.m4 

.PHONY : rpm docs test
rpm: dist
	cp $(PACKAGE)-$(VERSION).tar.gz ${HOME}/rpm/SOURCES/
	rpmbuild -ba $(PACKAGE).spec
	cp ${HOME}/rpm/RPMS/i386/$(PACKAGE)-$(VERSION)-*.i386.rpm .
	cp ${HOME}/rpm/SRPMS/$(PACKAGE)-$(VERSION)-*.src.rpm .

.PHONY : deb
deb: 
	debian/rules
	debuild
	debc
	debi
	release

packages: rpm

lint:
	make -C src lint
indent:
	make -C src indent

test:
	make -C test test

docs:
	doxygen docs/doxygen.conf
	make -C docs/doxygen/latex 
	dvips -f docs/doxygen/latex/refman.dvi > refman.ps
	ps2pdf refman.ps

grind:
	/bin/ls | valgrind --leak-check=yes -v --show-reachable=yes --track-fds=yes --gdb-attach=yes src/rand 2> dump

ACLOCAL_AMFLAGS = -I m4
