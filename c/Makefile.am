AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libwstoker.la
libwstoker_la_CFLAGS = \
    -g -Wall -O2 -fvisibility=hidden \
    -Iautogen/include \
    @CFC_C_INCLUDE@
libwstoker_la_LDFLAGS = -version-number 0:1:0
libwstoker_la_SOURCES = \
    ../core/LucyX/Analysis/WhitespaceTokenizer.c

autogen/hierarchy.json:
	@CFC@ --source=../core @CFC_INCLUDE@ --dest=autogen

$(libwstoker_la_OBJECTS): autogen/hierarchy.json

clean-local:
	-rm -rf autogen

