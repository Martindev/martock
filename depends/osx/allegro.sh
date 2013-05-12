sudo port install zlib freetype jpeg libogg physfs libpng flac \
                  libtheora +universal
sudo port upgrade --enforce-variants libpng +universal
git clone git://git.code.sf.net/p/alleg/allegro
cd allegro
mkdir build
cd build
cmake ..
make
sudo make install
