# Emergent

Emergent is a C++ framework for real-time 3D applications.

## Getting Started

### Dependencies

The following dependencies must be installed prior to building Emergent:

* [FreeType](https://www.freetype.org/)

On Debian "jessie" this can be done with the following command:

	apt-get install libfreetype6 libfreetype6-dev

The following dependencies are included with the Emergent source:

* [gl3w](https://github.com/skaslev/gl3w)
* [GLM](http://glm.g-truc.net)
* [stb_image](https://github.com/nothings/stb)

### Building and Installation

#### Windows

Building on Windows requires Visual Studio 2017 and CMake. Open the Visual Studio Command Prompt (VsDevCmd.bat) and run the following commands:

	cd emergent\build
	cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=<...>
	cmake --build .
	cmake --build . --target install

#### GNU/Linux

Building on GNU/Linux requires CMake and Make. Open a terminal and run the following commands:

	cd emergent/build
	cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=<...>
	cmake --build .
	cmake --build . --target install

### Documentation

The Emergent API reference can be generated with [Doxygen](http://www.stack.nl/~dimitri/doxygen/). First ensure the `doxygen` executable is in your system path, then execute the following command:

	cmake --build . --target emergent-docs

The output will be located in `docs/api-reference/html`.

## License

The source code for Emergent is licensed under the GNU General Public License, version 3. See [COPYING](./COPYING) for details.

Documentation text and assets for Emergent are licensed under a [Creative Commons Attribution-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-sa/4.0/).
