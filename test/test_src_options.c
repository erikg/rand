/*
 * $Id: test_src_options.c,v 1.1 2004/02/18 01:32:59 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "../src/options.h"

#include "test_src_options.h"

START_TEST (test_options1)
{
    char *argv[] = {"moocow", NULL};
    int argc = 1;
    FILE *io[2] = {NULL, NULL};
    char type;
    type = options(argc, argv, io);
    fail_unless(type==LINE, "Bad scramble type");
    fail_unless(io[0]==stdin, "stdin not set");
    fail_unless(io[1]==stdout, "stdin not set");
}
END_TEST

START_TEST (test_options2)
{
    char *argv[] = {"moocow", "-w", NULL};
    int argc = 2;
    FILE *io[2] = {NULL, NULL};
    char type;
    type = options(argc, argv, io);
    fail_unless(type==WORD, "Bad scramble type");
    fail_unless(io[0]==stdin, "stdin not set");
    fail_unless(io[1]==stdout, "stdin not set");
}
END_TEST

TCase *
src_options_test (Suite *s)
{
    TCase *tc_options = tcase_create ("options");
    tcase_add_test (tc_options, test_options1);
    tcase_add_test (tc_options, test_options2);

    return tc_options;
}

