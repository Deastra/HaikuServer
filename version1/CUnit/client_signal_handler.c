#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <err.h>
#include "../client.h"

void test_signal_handler_2(void) {
    CU_PASS(signal_handler(2));
}

void test_signal_handler_3(void) {
    CU_PASS(signal_handler(3));
}

int main() {
    if (CU_initialize_registry() != CUE_SUCCESS)
        errx(-1, "can't initialize test registry");
    CU_pSuite clientSuite = CU_add_suite("client", NULL, NULL);
    if (CU_get_error() != CUE_SUCCESS)
        errx(-1, "%s", CU_get_error_msg());
    CU_add_test(clientSuite, "signal_handler(2)", test_signal_handler_2);
    CU_add_test(clientSuite, "signal_handler(3)", test_signal_handler_3);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}