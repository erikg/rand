/*
 * $Id: test_rand.c,v 1.1 2004/02/16 14:31:07 erik Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <check.h>

START_TEST (test_create)
{
}
END_TEST


Suite *
rand_suite (void)
{
    Suite *s = suite_create ("rand");
    TCase *tc_core = tcase_create ("core");

    suite_add_tcase (s, tc_core);

    tcase_add_test (tc_core, test_create);
    return s;
}

int
main (void)
{
    int nf;
    Suite *s = rand_suite ();
    SRunner *sr = srunner_create (s);

    srunner_run_all (sr, CK_NORMAL);
    nf = srunner_ntests_failed (sr);
    srunner_free (sr);
    suite_free (s);
    return (nf == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
