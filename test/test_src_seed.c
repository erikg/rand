/*
 * $Id: test_src_seed.c,v 1.1 2004/02/18 03:29:35 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "../src/seed.h"

#include "test_src_seed.h"

START_TEST (test_seed1)
{
}
END_TEST

TCase *
src_seed_test (Suite *s)
{
    TCase *tc_seed = tcase_create ("seed");
    tcase_add_test (tc_seed, test_seed1);

    return tc_seed;
}

