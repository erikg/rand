/*
 * $Id: test_rand.c,v 1.3 2004/02/18 03:29:35 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "test_src_options.h"
#include "test_src_rand.h"
#include "test_src_seed.h"

Suite *
rand_suite (void)
{
    Suite *s = suite_create ("rand");

    suite_add_tcase (s, src_options_test(s));
    suite_add_tcase (s, src_seed_test(s));
    suite_add_tcase (s, src_rand_test(s));

    return s;
}

int
main (void)
{
    int nf;
    Suite *s = rand_suite ();
    SRunner *sr = srunner_create (s);

    srunner_set_log (sr, "test.log");
    srunner_run_all (sr, CK_NORMAL);
    nf = srunner_ntests_failed (sr);
    srunner_free (sr);
    suite_free (s);
    return (nf == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
