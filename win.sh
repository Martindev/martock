#!/bin/bash

flags="-o3 -Wall -g -ggdb -Iinclude -std=c99"

allegro="-lgcc_eh -static-libgcc -lallegro-5.0.8-monolith-static-mt            \
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
         -lgdi32 -lshell32 -lole32 -ladvapi32 -lws2_32 -lshlwapi -lstdc++      \
         -mwindows"

enet="-lenet -lwinmm -lws2_32"

sources="$(echo src/*.c) $(echo src/*/*.c)"

gcc $flags $sources -o martock $allegro $enet
