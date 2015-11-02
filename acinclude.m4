AC_DEFUN(AC_CHECK_NEXTAW,
[
AC_ARG_ENABLE(obsolete_selections,
	[  --enable-obsolete-selections    Use CUT_BUFFER stuff from X10],
	[ if test "$withval" = yes; then
		AC_DEFINE(OBSOLETE_SELECTIONS, 1, [#undef OBSOLETE_SELECTIONS])
	fi ])

dnl Check for wide chars
AC_CHECK_HEADER(wctype.h, AC_DEFINE(HAS_WCTYPE_H))
AC_CHECK_HEADER(widec.h, AC_DEFINE(HAS_WIDEC_H))
AC_CHECK_HEADER(wchar.h, AC_DEFINE(HAS_WCHAR_H))
AC_CHECK_HEADER(X11/Xmu/Xmu.h, AC_DEFINE(HAS_XMU_H))
AC_CHECK_FUNC(wcslen, , AC_DEFINE(USE_XWCHAR_STRING))
AC_CHECK_FUNC(mbtowc, , AC_DEFINE(USE_XMBTOWC))
AC_CHECK_FUNCS(wslen wscpy wsncpy)

LDFLAGS="$LDFLAGS $X_LIBS"
dnl AC_CHECK_LIB(X11, main)
dnl AC_CHECK_LIB(Xt, main)
AC_CHECK_LIB(Xext, main)
AC_CHECK_LIB(Xmu, main)

dnl Generate warnings
if test "$GCC" = "yes"; then
        CFLAGS="-Wall $CFLAGS"
fi

dnl Set NARROWPROTO
case "$host_os" in
freebsd*|gnu*|irix5*|irix6*|linux-gnu*|netbsd*|openbsd*)
        CFLAGS="-DNARROWPROTO=1 $CFLAGS"
esac
])
