#define CFISH_USE_SHORT_NAMES
#define WSTOKER_USE_SHORT_NAMES
#define TESTWSTOKER_USE_SHORT_NAMES

#define C_TESTWSTOKER_TESTWHITESPACETOKENIZER
#include "LucyX/Test/Analysis/TestWhitespaceTokenizer.h"

#include "Clownfish/String.h"
#include "Clownfish/TestHarness/TestBatchRunner.h"
#include "Clownfish/VArray.h"
#include "Clownfish/VTable.h"
#include "LucyX/Analysis/WhitespaceTokenizer.h"

void
testwstoker_init_parcel() {
}

TestWhitespaceTokenizer*
TestWhitespaceTokenizer_new() {
    return (TestWhitespaceTokenizer*)VTable_Make_Obj(TESTWHITESPACETOKENIZER);
}

static void
test_tokenizer(TestBatchRunner *runner) {
    WhitespaceTokenizer *toker = WhitespaceTokenizer_new();
    WhitespaceTokenizer *other = WhitespaceTokenizer_new();

    TEST_TRUE(runner, WhitespaceTokenizer_Equals(toker, (Obj*)other),
              "Equals");

    static const char text_buf[] =
        " "
        ".tha\xCC\x82t's"
        "\t"
        "1,02\xC2\xADZ4.38"
        "\r\n"
        "\xE0\xB8\x81\xC2\xAD\xC2\xAD"
        "   "
        "\xF0\xA0\x80\x80//"
        " \t\n";
    String *text = Str_new_from_utf8(text_buf, sizeof(text_buf) - 1);
    VArray *got = WhitespaceTokenizer_Split(toker, text);

    VArray *expect = VA_new(4);
    VA_Push(expect, (Obj*)Str_newf(".tha\xCC\x82t's"));
    VA_Push(expect, (Obj*)Str_newf("1,02\xC2\xADZ4.38"));
    VA_Push(expect, (Obj*)Str_newf("\xE0\xB8\x81\xC2\xAD\xC2\xAD"));
    VA_Push(expect, (Obj*)Str_newf("\xF0\xA0\x80\x80//"));

    TEST_TRUE(runner, VA_Equals(got, (Obj*)expect), "Split");

    DECREF(expect);
    DECREF(got);
    DECREF(text);
    DECREF(other);
    DECREF(toker);
}

void
TestWhitespaceTokenizer_Run_IMP(TestWhitespaceTokenizer *self,
                                TestBatchRunner *runner) {
    TestBatchRunner_Plan(runner, (TestBatch*)self, 2);
    test_tokenizer(runner);
}

