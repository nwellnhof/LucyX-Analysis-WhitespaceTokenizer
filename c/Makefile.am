AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libwstoker.la
libwstoker_la_CFLAGS = \
    -std=c99 -g -Wall -O2 -fvisibility=hidden \
    -DCFP_WSTOKER \
    -Iautogen/include \
    @CFC_C_INCLUDE@
libwstoker_la_LDFLAGS = -version-number 0:1:0
libwstoker_la_SOURCES = \
    ../core/LucyX/Analysis/WhitespaceTokenizer.c \
    autogen/source/wstoker_parcel.c

check_PROGRAMS = tests/test_wstoker
tests_test_wstoker_SOURCES = \
    ../core/LucyX/Test/Analysis/TestWhitespaceTokenizer.c \
    autogen/source/testwstoker_parcel.c \
    tests/test_wstoker.c
tests_test_wstoker_CFLAGS = \
    -std=c99 -g -Wall -O2 \
    -Iautogen/include \
    @CFC_C_INCLUDE@
tests_test_wstoker_LDADD = libwstoker.la

autogen/hierarchy.json:
	@CFC@ --source=../core @CFC_INCLUDE@ --dest=autogen

$(libwstoker_la_OBJECTS): autogen/hierarchy.json

clean-local:
	-rm -rf autogen

