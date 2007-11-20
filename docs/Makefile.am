########################################################################
# rand                                                                 #
# Copyright (C) 1998-2007 Erik Greenwald <erik@smluc.org>              #
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

# $Id: Makefile.am,v 1.4 2007/11/20 21:00:12 erik Exp $

man_MANS = rand.1

EXTRA_DIST=$(man_MANS)

rand.ps: rand.1
	groff -t -e -mandoc $< -Tps > $>

rand.pdf: rand.ps
	ps2pdf rand.ps rand.pdf

rand.html: rand.1
	cat $< | man2html > $@

clean:
	rm -rf doxygen rand.ps rand.pdf
