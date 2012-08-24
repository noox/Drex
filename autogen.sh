
#!/bin/sh

# simple autogen script that generates basic layout for autotools.

MY_CPPFLAGS="-I/usr/local/include -I\$(srcdir)/include/"
MY_CFLAGS="-Wall"
MY_LDFLAGS="-L/usr/local/lib"
MY_LDADD="-lGL -lGLU -lSDL -lSDL_image"

OUT=Makefile.am
touch NEWS AUTHORS ChangeLog
echo > $OUT

DISTDIRS=""

echo "AUTOMAKE_OPTIONS = subdir-objects" >>$OUT
echo "dist_noinst_SCRIPTS = autogen.sh" `for i in $DISTDIRS ; do find \$i -type f ; done | tr "\n" " " ` >>$OUT

echo "bin_PROGRAMS = drex" >>$OUT
echo "drexdir = src/" >>$OUT
echo "drex_SOURCES = `( find src/ -type f -name \*.c ; find src/ -type f -name \*.cpp ) |tr \"\n\" \" \" ` " >>$OUT
echo "noinst_HEADERS = `find src/ -type f -name \*.h |tr \"\n\" \" \" `" >>$OUT
echo "drex_CPPFLAGS = -I\$(srcdir)/$i/ ${MY_CPPFLAGS}" >>$OUT
echo "drex_CFLAGS = ${MY_CFLAGS}" >>$OUT
echo "drex_LDFLAGS = ${MY_LDFLAGS}" >>$OUT
echo "drex_LDADD = ${MY_LDADD} " >>$OUT

libtoolize --force && aclocal && autoconf && automake --add-missing

