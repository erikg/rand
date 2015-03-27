########################################################################
# rand                                                                 #
# Copyright (C) 1998-2015 Erik Greenwald <erik@elfga.com>              #
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

TESTS=test_rand
noinst_PROGRAMS=test_rand
rand_src = $(top_srcdir)/src/help.c $(top_srcdir)/src/options.c $(top_srcdir)/src/rand.c $(top_srcdir)/src/seed.c
test_rand_SOURCES=test_rand.c test_src_options.c test_src_rand.c test_src_seed.c $(rand_src) $(rand_src:.c=.h)
noinst_HEADERS=test_src_options.h test_src_rand.h test_src_seed.h

AM_CFLAGS = @CHECK_CFLAGS@ @COVERAGE_CFLAGS@
LDADD  = @CHECK_LIBS@ @LIBINTL@

test: test_rand
	./test_rand

clean-local:
	rm -f *.bb *.bbg *.da test.log

