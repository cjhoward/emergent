# Emergent

Emergent is a C++ framework for real-time 3D applications.

## Getting Started

### Dependencies

The following dependencies must be installed prior to building Emergent:

* [FreeType](https://www.freetype.org/)

The following dependencies are included with the Emergent source:

* [gl3w](https://github.com/skaslev/gl3w)
* [GLM](http://glm.g-truc.net)
* [stb_image](https://github.com/nothings/stb)

### Building and Installation

**1. Install the required dependencies.** On Debian "jessie" this can be done with the following command:

	apt-get install libfreetype6 libfreetype6-dev

**2. Configure with CMake.** The following example configures a debug build for a unix-based platform:

	cmake . -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug

**3. Build**

	cmake --build .

**4. Install**

	cmake --build . --target install

### Documentation

The Emergent API reference can be generated with [Doxygen](http://www.stack.nl/~dimitri/doxygen/) using the following commands:

	cd docs/api-reference
	doxygen

## License

The source code for Emergent is licensed under the GNU General Public License, version 3. See [COPYING](./COPYING) for details.

Documentation text and assets for Emergent are licensed under a [Creative Commons Attribution-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-sa/4.0/).
