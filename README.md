# Dependencies

* STB
* Catch2

# Build

Resolve and install dependencies. Build packages from source whose binary package is not found.

    $ conan install . --output-folder=build --build=missing

Build the source code.

    $ cd build
    $ cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
    $ cmake --build .
