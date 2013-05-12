#!/bin/bash

flags="-o3 -Wall -g -ggdb -Iinclude -std=c99"

allegro="$(pkg-config --libs --static allegro-static-5.0           \
         allegro_image-static-5.0 allegro_acodec-static-5.0        \
         allegro_font-static-5.0 allegro_color-static-5.0          \
         allegro_audio-static-5.0 allegro_main-static-5.0          \
         allegro_memfile-static-5.0 allegro_primitives-static-5.0  \
         allegro_ttf-static-5.0)"

enet="-lenet"

sources="$(echo src/*.c) $(echo src/*/*.c)"

gcc $flags $sources -o martock $allegro $enet