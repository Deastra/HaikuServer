#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <err.h>
#include "../server.h"

void test_signal_handler_2(void) {
    CU_ASSERT_EQUAL(signal_handler(2), 1);
}

void test_signal_handler_3(void) {
    CU_ASSERT_EQUAL(signal_handler(3), 2);
}

void test_signal_handler_1(void) {
    CU_ASSERT_EQUAL(signal_handler(1), 0);
}

void test_signal_handler_4(void) {
    CU_ASSERT_EQUAL(signal_handler(4), 0);
}

int main() {
    if (CU_initialize_registry() != CUE_SUCCESS)
        errx(-1, "can't initialize test registry");
    CU_pSuite serverSuite = CU_add_suite("server", NULL, NULL);
    if (CU_get_error() != CUE_SUCCESS)
        errx(-1, "%s", CU_get_error_msg());
    CU_add_test(serverSuite, "signal_handler(2)", test_signal_handler_2);
    CU_add_test(serverSuite, "signal_handler(3)", test_signal_handler_3);
    CU_add_test(serverSuite, "signal_handler(1)", test_signal_handler_1);
    CU_add_test(serverSuite, "signal_handler(4)", test_signal_handler_4);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}