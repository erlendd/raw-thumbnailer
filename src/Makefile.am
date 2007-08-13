raw_thumbnailerdir=$(bindir)
raw_thumbnailer_PROGRAMS=raw-thumbnailer
raw_thumbnailer_SOURCES=main.cpp

INCLUDES = $(OPENRAW_CFLAGS)      \
           $(OPENRAWGNOME_CFLAGS) \
           $(GDK_CFLAGS)

raw_thumbnailer_LDADD = $(GDK_LIBS) $(OPENRAW_LIBS) $(OPENRAWGNOME_LIBS)

