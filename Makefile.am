# $Id: Makefile.am,v 1.12 2004/07/05 14:10:15 erik Exp $
#

#if TEST
#TEST=test
#endif
TEST=

SUBDIRS = po src docs $(TEST)

EXTRA_DIST=ChangeLog $(PACKAGE).spec.in rand.lsm.in

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
