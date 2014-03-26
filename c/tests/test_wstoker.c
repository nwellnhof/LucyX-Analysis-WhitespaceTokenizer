#include <stdlib.h>

#define CFISH_USE_SHORT_NAMES
#define TESTWSTOKER_USE_SHORT_NAMES
#include "Clownfish/TestHarness/TestFormatter.h"
#include "Clownfish/TestHarness/TestSuite.h"
#include "LucyX/Test/Analysis/TestWhitespaceTokenizer.h"

int
main() {
    TestFormatter *formatter;
    TestSuite     *suite;
    bool success;

    testwstoker_bootstrap_parcel();

    suite = TestSuite_new();
    TestSuite_Add_Batch(suite, (TestBatch*)TestWhitespaceTokenizer_new());
    formatter = (cfish_TestFormatter*)cfish_TestFormatterCF_new();
    success = CFISH_TestSuite_Run_All_Batches(suite, formatter);

    CFISH_DECREF(formatter);
    CFISH_DECREF(suite);
    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}

