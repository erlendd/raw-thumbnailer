#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.50)
AC_INIT(raw-thumbnailer, 0.2, erlend.davidson@gmail.com)
AC_CONFIG_SRCDIR([src/main.c])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADER([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL

# Checks for libraries.
PKG_CHECK_MODULES(OPENRAW, libopenraw-1.0, HAVE_OPENRAW=yes)
PKG_CHECK_MODULES(OPENRAWGNOME, libopenraw-gnome-1.0, HAVE_OPENRAWGNOME=yes)
PKG_CHECK_MODULES(GDK, gdk-pixbuf-2.0, HAVE_GDK=yes)

AC_SUBST(OPENRAW_CFLAGS)
AC_SUBST(OPENRAW_LIBS)
AC_SUBST(OPENRAWGNOME_CFLAGS)
AC_SUBST(OPENRAWGNOME_LIBS)

# Checks for header files.
#AC_CHECK_HEADERS(gdkpixbuf.h rawfile.h thumbnail.h debug.h libopenraw.h, HAVE_HEADERS=yes)
#if test -z "$HAVE_HEADERS"; then
#    AC_MSG_ERROR([Error locating headers])
#fi

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.

#AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
