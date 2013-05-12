#!/bin/bash

flags="-Wall -g -ggdb"

allegro="$(pkg-config --libs --static allegro-static-5.0           \
         allegro_image-static-5.0 allegro_acodec-static-5.0        \
         allegro_font-static-5.0 allegro_color-static-5.0          \
         allegro_audio-static-5.0 allegro_main-static-5.0          \
         allegro_memfile-static-5.0 allegro_primitives-static-5.0  \
         allegro_ttf-static-5.0)"

enet="-lenet"

sources="src/martock.c"

gcc $flags $sources -o martock $allegro
