AC_INIT([wstoker], [0.1.0])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE

LT_INIT([disable-static])

AC_PROG_CC
AC_PROG_MAKE_SET

AC_ARG_WITH([clownfish],
    [AS_HELP_STRING(
        [--with-clownfish=PREFIX],
        [Use Clownfish installation in PREFIX])])

CFC=cfc
CFC_INCLUDE=
CFC_C_INCLUDE="-I/usr/local/share/clownfish/include -I/usr/share/clownfish/include"
AS_IF([test "x$with_clownfish" != x], [
    CFC="$with_clownfish/bin/cfc"
    CFC_INCLUDE="--include=$with_clownfish/share/clownfish/include"
    CFC_C_INCLUDE="-I$with_clownfish/share/clownfish/include"
    LDFLAGS="$LDFLAGS -L$with_clownfish/lib"
])
AC_SUBST([CFC])
AC_SUBST([CFC_INCLUDE])
AC_SUBST([CFC_C_INCLUDE])

AC_CHECK_LIB([cfish], [cfish_bootstrap_parcel], [],
    [AC_MSG_ERROR([libcfish not found])])
AC_CHECK_LIB([lucy], [lucy_bootstrap_parcel], [],
    [AC_MSG_ERROR([liblucy not found])])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

