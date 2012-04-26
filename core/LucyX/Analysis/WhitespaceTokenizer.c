#define WHITESPACETOKENIZER_USE_SHORT_NAMES
#define LUCY_USE_SHORT_NAMES

#define C_WHITESPACETOKENIZER_WHITESPACETOKENIZER
#define C_LUCY_TOKEN
#include "Lucy/Util/ToolSet.h"

#include "LucyX/Analysis/WhitespaceTokenizer.h"
#include "Lucy/Analysis/Inversion.h"
#include "Lucy/Analysis/Token.h"
#include "Lucy/Util/StringHelper.h"

#include <ctype.h>

void
whitespacetokenizer_init_parcel() {
}

WhitespaceTokenizer*
WhitespaceTokenizer_new() {
    WhitespaceTokenizer *self
        = (WhitespaceTokenizer*)VTable_Make_Obj(WHITESPACETOKENIZER);
    return WhitespaceTokenizer_init(self);
}

WhitespaceTokenizer*
WhitespaceTokenizer_init(WhitespaceTokenizer *self) {
    Analyzer_init((Analyzer*)self);
    return self;
}

Inversion*
WhitespaceTokenizer_transform(WhitespaceTokenizer *self, Inversion *inversion) {
    Inversion *new_inversion = Inversion_new(NULL);
    Token *token;

    while (NULL != (token = Inversion_Next(inversion))) {
        WhitespaceTokenizer_Tokenize_Str(self, token->text, token->len,
                                         new_inversion);
    }

    return new_inversion;
}

Inversion*
WhitespaceTokenizer_transform_text(WhitespaceTokenizer *self, CharBuf *text) {
    Inversion *new_inversion = Inversion_new(NULL);
    WhitespaceTokenizer_Tokenize_Str(self, (char*)CB_Get_Ptr8(text),
                                     CB_Get_Size(text), new_inversion);
    return new_inversion;
}

void
WhitespaceTokenizer_tokenize_str(WhitespaceTokenizer *self, const char *text,
                                 size_t len, Inversion *inversion) {
    size_t byte_pos       = 0;
    size_t char_pos       = 0;
    size_t start_byte_pos = 0;
    size_t start_char_pos = 0;
    int    prev_ws        = 1;

    while (byte_pos < len) {
        uint32_t cp = StrHelp_decode_utf8_char(text + byte_pos);
        int      ws = isspace(cp);

        if (prev_ws && !ws) {
            start_byte_pos = byte_pos;
            start_char_pos = char_pos;
        }
        else if (!prev_ws && ws) {
            Token *token = Token_new(text + start_byte_pos,
                                     byte_pos - start_byte_pos,
                                     start_char_pos, char_pos, 1.0f, 1);
            Inversion_Append(inversion, token);
        }

        prev_ws = ws;
        byte_pos += StrHelp_UTF8_COUNT[text[byte_pos]];
        char_pos += 1;
    }

    if (!prev_ws) {
        Token *token = Token_new(text + start_byte_pos,
                                 byte_pos - start_byte_pos,
                                 start_char_pos, char_pos, 1.0f, 1);
        Inversion_Append(inversion, token);
    }
}

bool_t
WhitespaceTokenizer_equals(WhitespaceTokenizer *self, Obj *other) {
    WhitespaceTokenizer *const twin = (WhitespaceTokenizer*)other;
    if (twin == self)                          { return true; }
    if (!Obj_Is_A(other, WHITESPACETOKENIZER)) { return false; }
    return true;
}


