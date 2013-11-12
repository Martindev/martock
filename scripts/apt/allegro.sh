sudo apt-get update
wget http://cdn.allegro.cc/file/library/allegro/5.0.8/allegro-5.0.8.tar.gz
tar -xzvf allegro-5.0.8.tar.gz
cd allegro-5.0.8
sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev
sudo apt-get install -y cmake g++ freeglut3-dev libxcursor-dev libpng12-dev \
                        libjpeg-dev libfreetype6-dev libgtk2.0-dev          \
                        libasound2-dev libpulse-dev libopenal-dev           \
                        libflac-dev libdumb1-dev libvorbis-dev libphysfs-dev
mkdir build
cd build
cmake -DSHARED=off ..
make
sudo make install
