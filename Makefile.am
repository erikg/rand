# $Id: Makefile.am,v 1.10 2004/04/11 17:22:09 erik Exp $
#

if HAVE_TEST
TEST=test
endif

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
