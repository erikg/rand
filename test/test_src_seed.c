
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

