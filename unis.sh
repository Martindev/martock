#!/bin/bash

flags="-o3 -Wall -g -ggdb -Iinclude -std=c99"

allegro="$(pkg-config --libs allegro-5.0 \
allegro_image-5.0 allegro_acodec-5.0 \
allegro_font-5.0 allegro_color-5.0 \
allegro_audio-5.0 allegro_main-5.0 \
allegro_memfile-5.0 allegro_primitives-5.0 \
allegro_ttf-5.0)"

enet="-lenet"

sources="$(echo src/*.c) $(echo src/*/*.c)"

gcc $flags $sources -o martock $allegro $enet
