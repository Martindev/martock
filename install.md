On Unix/Linux systems, run

    sh unix.sh

If you're on Windows, you need to build in an environment like Cygwin or Msys,
and run

    sh win.sh

To run it, you'll need to get the media assets, which can be automatically done
by running

    sh assets.sh
    
If you get an error like "wget not recognized" in msys, run

    mingw-get install msys-wget-bin
