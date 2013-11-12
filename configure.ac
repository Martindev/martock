AC_INIT([Martock],
        [0.0.0],
        [https://github.com/Martindev/Martock/issues],
        [martock],
        [https://github.com/Martindev/Martock])

AC_PROG_CC_C99
AC_CHECK_HEADER(allegro5/allegro.h)

AS_IF([test ! -d assets],[mkdir assets],[echo Assets directory exists.])

AS_IF([test x"$SYS" = xlin],
      [allegro="$(pkg-config --libs --static allegro-static-5.0           \
                allegro_image-static-5.0 allegro_acodec-static-5.0        \
                allegro_font-static-5.0 allegro_color-static-5.0          \
                allegro_audio-static-5.0 allegro_main-static-5.0          \
                allegro_memfile-static-5.0 allegro_primitives-static-5.0  \
                allegro_ttf-static-5.0)"],
      [test x"$SYS" = xwin],
      [allegro="-mwindows -lgcc_eh -static-libgcc -lstdc++-6                          \
                -lallegro-5.0.8-monolith-static-mt                                    \
                -lallegro_acodec-5.0.8-static-mt -lallegro_audio-5.0.8-static-mt      \
                -lopenal-1.14-static-mt -lvorbisfile-1.3.2-static-mt                  \
                -lvorbis-1.3.2-static-mt -lallegro_color-5.0.8-static-mt              \
                -lallegro_dialog-5.0.8-static-mt -lallegro_font-5.0.8-static-mt       \
                -lallegro_image-5.0.8-static-mt -lallegro_memfile-5.0.8-static-mt     \
                -lallegro_physfs-5.0.8-static-mt -lallegro_primitives-5.0.8-static-mt \
                -lallegro_ttf-5.0.8-static-mt -ldumb-0.9.3-static-mt                  \
                -lFLAC-1.2.1-static-mt -lfreetype-2.4.8-static-mt                     \
                -logg-1.2.1-static-mt -lzlib-1.2.5-static-mt -lgdiplus -luuid         \
                -lkernel32 -lwinmm -lpsapi -lopengl32 -lglu32 -luser32 -lcomdlg32     \
                -lgdi32 -lshell32 -lole32 -ladvapi32 -lws2_32 -lshlwapi"],
        [test x"$SYS" = xosx],
        [allegro="$(pkg-config --libs allegro-5.0            \
                  allegro_image-5.0 allegro_acodec-5.0       \
                  allegro_font-5.0 allegro_color-5.0         \
                  allegro_audio-5.0 allegro_main-5.0         \
                  allegro_memfile-5.0 allegro_primitives-5.0 \
                  allegro_ttf-5.0)"])

CFLAGS="$CFLAGS -Wall -g -ggdb -Isrc/include"

AC_SUBST(allegro)

AS_IF([test -e assets/blocks.tga],
      [echo Have texture.],
      [wget https://dl.dropboxusercontent.com/u/51727789/assets/blocks.tga -P assets/])

AS_IF([test -e assets/font.ttf],
      [echo Have font.],
      [wget https://dl.dropboxusercontent.com/u/51727789/assets/font.ttf -P assets/])

AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
