# Building instructions with CMake
* Make sure you have cmake installed (of version 3.0 or above)
* Make sure you have packages: "qtbase5-dev", "qtdeclarative5-dev", "libqt5multimedia5-plugins" and "libtag1-dev" installed in order to build
* You can install these with "sudo apt install cmake qtbase5-dev qtdeclarative5-dev libqt5multimedia5-plugins libtag1-dev" if you have ubuntu or debian
* In order to run the application or the tests, you need to build with "./cmake-build". This creates the executables in the "build" directory. You might need to give it permissions in order to run it, like: "sudo chmod +x cmake-build"
* To run the program, use the script "./run" and to run the tests use "./run-test". This might require you to give it permissions like above.
