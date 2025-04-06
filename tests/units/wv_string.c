#include "../include/acutest.h"

#define WV_STRING_IMPLEMENTATION
#include "../../wv_string.h"


void wv_string_demo_test(void) {
    wv_string_demo();
    TEST_ASSERT(1 != 0);
}


TEST_LIST = {
    { "wv_string_demo", wv_string_demo_test },
    { NULL, NULL }
};
