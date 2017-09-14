# Emergent

Emergent is a C++ framework for real-time 3D applications.

## Building and Installation

### GNU/Linux

Building on GNU/Linux requires CMake, GCC, G++, and GNU Make. Open a terminal and run the following commands:

	cd emergent/build
	cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=<...>
	cmake --build .
	cmake --build . --target install

### Windows

Building on Windows requires CMake and Visual Studio 2017. Open the Visual Studio Native Tools Command Prompt, navigate to the project root directory, then run the following commands:

	cd emergent\build
	cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=<...>
	cmake --build .
	cmake --build . --target install

## Documentation

The Emergent API reference can be generated with [Doxygen](http://www.stack.nl/~dimitri/doxygen/). First ensure the `doxygen` executable is in your system path, then execute the following command:

	cmake --build . --target emergent-docs

The output will be located in `docs/api-reference/html`.

## License

The source code for Emergent is licensed under the GNU General Public License, version 3. See [COPYING](./COPYING) for details.

Documentation text and assets for Emergent are licensed under a [Creative Commons Attribution-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-sa/4.0/).
