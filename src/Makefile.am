########################################################################
# rand                                                                 #
# Copyright (C) 1998-2012 Erik Greenwald <erik@brlcad.org>              #
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
