
#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "../src/rand.h"

#include "test_src_rand.h"

START_TEST (test_rand1)
{
}
END_TEST

TCase *
src_rand_test (Suite *s)
{
    TCase *tc_rand = tcase_create ("rand");
    tcase_add_test (tc_rand, test_rand1);

    return tc_rand;
}

