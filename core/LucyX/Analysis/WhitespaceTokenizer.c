#define WSTOKER_USE_SHORT_NAMES
#define CFISH_USE_SHORT_NAMES
#define LUCY_USE_SHORT_NAMES

#define C_WSTOKER_WHITESPACETOKENIZER
#include "LucyX/Analysis/WhitespaceTokenizer.h"

#include "Clownfish/Class.h"
#include "Clownfish/Obj.h"
#include "Clownfish/String.h"
#include "Clownfish/Util/StringHelper.h"
#include "Lucy/Analysis/Inversion.h"
#include "Lucy/Analysis/Token.h"

#include <ctype.h>

void
wstoker_init_parcel() {
}

WhitespaceTokenizer*
WhitespaceTokenizer_new() {
    WhitespaceTokenizer *self
        = (WhitespaceTokenizer*)Class_Make_Obj(WHITESPACETOKENIZER);
    return WhitespaceTokenizer_init(self);
}

WhitespaceTokenizer*
WhitespaceTokenizer_init(WhitespaceTokenizer *self) {
    Analyzer_init((Analyzer*)self);
    return self;
}

Inversion*
WhitespaceTokenizer_Transform_IMP(WhitespaceTokenizer *self,
                                  Inversion *inversion) {
    Inversion *new_inversion = Inversion_new(NULL);
    Token *token;

    while (NULL != (token = Inversion_Next(inversion))) {
        WhitespaceTokenizer_Tokenize_Str(self, Token_Get_Text(token),
                                         Token_Get_Len(token), new_inversion);
    }

    return new_inversion;
}

Inversion*
WhitespaceTokenizer_Transform_Text_IMP(WhitespaceTokenizer *self,
                                       String *text) {
    Inversion *new_inversion = Inversion_new(NULL);
    WhitespaceTokenizer_Tokenize_Str(self, (char*)Str_Get_Ptr8(text),
                                     Str_Get_Size(text), new_inversion);
    return new_inversion;
}

void
WhitespaceTokenizer_Tokenize_Str_IMP(WhitespaceTokenizer *self,
                                     const char *text, size_t len,
                                     Inversion *inversion) {
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
        byte_pos += StrHelp_UTF8_COUNT[(uint8_t)text[byte_pos]];
        char_pos += 1;
    }

    if (!prev_ws) {
        Token *token = Token_new(text + start_byte_pos,
                                 byte_pos - start_byte_pos,
                                 start_char_pos, char_pos, 1.0f, 1);
        Inversion_Append(inversion, token);
    }
}

bool
WhitespaceTokenizer_Equals_IMP(WhitespaceTokenizer *self, Obj *other) {
    WhitespaceTokenizer *const twin = (WhitespaceTokenizer*)other;
    if (twin == self)                          { return true; }
    if (!Obj_Is_A(other, WHITESPACETOKENIZER)) { return false; }
    return true;
}


