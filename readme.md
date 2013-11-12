![Martock](http://i.imgur.com/4wGwPr5.png)
================================================================================

Martock is a clone of Terraria, a project we are using to learn C, databases,
version control, and an array of other things.

This readme is currently a stub. For development information, see standards.md
and todo.md. Installation information is below.

Martock can be installed on most Debian and Ubuntu Linux distrobutions, and on
Windows using an environment like Cygwin or Msys. It can (maybe) be installed
on OSX. To install it, do the dance

    autoreconf -vfi
    ./configure SYS=[lin|win|osx]
    make

Once it's done you'll have a binary called *martock* in the directory. The SYS
variable is required, and on linux it would like this

    ./configure SYS=lin

Allegro is required to build Martock. There are scripts in the scripts folder
to install allegro automatically on OSX with Macports and Linux machines with
apt. Otherwise you're on your own unfortunately.

If you get an error like "wget not recognized" in msys, run

    mingw-get install msys-wget-bin
