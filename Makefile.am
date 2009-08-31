########################################################################
# rand                                                                 #
# Copyright (C) 1998-2009 Erik Greenwald <erik@smluc.org>              #
#                                                                      #
# This program is free software; you can redistribute it and/or modify #
# it under the terms of the GNU General Public License as published by #
# the Free Software Foundation; either version 2 of the License, or    #
# (at your option) any later version.                                  #
#                                                                      #
# This program is distributed in the hope that it will be useful,      #
# but WITHOUT ANY WARRANTY; without even the implied warranty of       #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        #
# GNU General Public License for more details.                         #
#                                                                      #
# You should have received a copy of the GNU General Public License    #
# along with this program; if not, write to the Free Software          #
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.            #
#                                                                      #
########################################################################

# $Id: Makefile.am,v 1.25 2009/08/31 17:40:38 erik Exp $

#if TEST
#TEST=test
#endif
TEST=

SUBDIRS = debian m4 src docs po $(TEST)

.PHONY : rpm docs test indent lint grind hist histo histogram
rpm: dist
	cp $(PACKAGE)-$(VERSION).tar.gz /usr/src/rpm/SOURCES/
	rpmbuild -ba $(PACKAGE).spec
	cp /usr/src/rpm/RPMS/i386/$(PACKAGE)-$(VERSION)-*.i386.rpm .
	cp /usr/src/rpm/SRPMS/$(PACKAGE)-$(VERSION)-*.src.rpm .

.PHONY : deb
deb: dist
	rm -rf $(PACKAGE)-$(VERSION)
	tar zxvf $(PACKAGE)-$(VERSION).tar.gz
	(cd $(PACKAGE)-$(VERSION) && fakeroot debian/rules binary)
	(cd $(PACKAGE)-$(VERSION) && debuild -us -uc)
	rm -rf $(PACKAGE)-$(VERSION)

lint indent:
	make -C src $@

test:
	make -C test test

docs:
	doxygen docs/doxygen.conf
	make -C docs/doxygen/latex
	dvips -f docs/doxygen/latex/refman.dvi > refman.ps
	ps2pdf refman.ps

grind:
	/bin/ls | valgrind --leak-check=yes -v --show-reachable=yes --track-fds=yes src/rand 2> dump

hist histo histogram:
	for a in `head -n 1000 config.log` ; do /bin/ls | src/rand | head -n 1 ; done | sort | uniq -c | sort -nr

fhist fhisto fhistogram:
	for a in `head -n 100 config.log` ; do /bin/ls | src/rand | head -n 1 ; done | sort | uniq -c | sort -nr

EXTRA_DIST= config.rpath ChangeLog $(PACKAGE).spec.in rand.lsm.in TODO

ACLOCAL_AMFLAGS = -I m4
