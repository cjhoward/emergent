# Emergent &middot; [![GitHub license](https://img.shields.io/github/license/cjhoward/emergent.svg)](https://github.com/cjhoward/emergent/blob/master/COPYING) [![GitHub release](https://img.shields.io/github/release/cjhoward/emergent.svg)](https://github.com/cjhoward/emergent/releases/)

Emergent is a cross-platform compatible C++ framework for real-time 3D applications.

## Table of Contents

* [Installation](#installation)
	* [Download](#download)
	* [Configure](#configure)
	* [Build on GNU/Linux](#build-on-gnulinux)
	* [Build on Windows](#build-on-windows)
	* [Install](#install)
* [Documentation](#documentation)
* [Examples](#examples)
* [License](#license)

## Installation

### Download

Use Git to download the Emergent repository and its submodules:

	git clone --recursive https://github.com/cjhoward/emergent.git emergent

### Configure

Emergent uses a CMake build system to configure, build, and install Emergent and its dependencies. Ensure CMake is installed before proceeding.

The following basic CMake configuration options are available:

| Option                        | Description                                                                     |
| ----------------------------- | ------------------------------------------------------------------------------- |
| `BUILD_DOCS:BOOL=OFF`         | Build the API reference docs using Doxygen.                                     |
| `BUILD_EXAMPLES:BOOL=ON`      | Build the example programs.                                                     |
| `BUILD_STATIC:BOOL=ON`        | Build a static version of the library.                                          |
| `CMAKE_BUILD_TYPE:STRING=`    | Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel. |
| `CMAKE_INSTALL_PREFIX:PATH=`  | Install path prefix, prepended onto install directories.                        |
| `DOXYGEN_BINARY:PATH=doxygen` | Path to the Doxygen binary.                                                     |

For a full list of advanced CMake configuration options, run the command `cmake .. -LAH` from the `build` directory.

### Build on GNU/Linux

Building on GNU/Linux requires GCC, G++, and GNU Make. Open a command prompt in the `build` directory then run the following commands:

	cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=<...>
	cmake --build .

### Build on Windows

Building on Windows requires Visual Studio 2017. Open the Visual Studio Native Tools Command Prompt in the `build` directory then run the following commands:

	cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=<...>
	cmake --build .

### Install

Run the following command to install Emergent and its dependencies in the directory specified by the `CMAKE_INSTALL_PREFIX` option:

	cmake --build . --target install

## Documentation

The Emergent API reference can be found [here](https://cjhoward.org/emergent/api-reference).

## Examples

Creating an application with Emergent is as simple as deriving from the `Emergent::Application` class and calling its `execute()` function:

	#include <emergent/emergent.hpp>

	class ExampleApplication: public Emergent::Application {};

	int main(int argc, char* argv[])
	{
		return ExampleApplication().execute();
	}

The `Emergent::Application` class provides virtual functions such as `setup()`, `update()`, `render()`, and `exit()`, which are called from within the `execute()` function and can be overridden.

To build an Emergent application using CMake, set `CMAKE_PREFIX_PATH` to the location at which Emergent was installed then add the following to your `CMakeLists.txt`:

	find_package(emergent REQUIRED CONFIG)
	add_executable(${EXECUTABLE_TARGET} ${SOURCE_FILES})
	target_link_libraries(${EXECUTABLE_TARGET} emergent)

Where `${EXECUTABLE_TARGET}` is your application's executable target and `${SOURCE_FILES}` is a list of your application's source files.

For more in-depth examples, see the [`modules/emergent/src/examples`](./modules/emergent/src/examples) directory.

## License

The source code for Emergent is licensed under the GNU General Public License, version 3. See [`COPYING`](./COPYING) for details.

Documentation text and assets for Emergent are licensed under a [Creative Commons Attribution-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-sa/4.0/).

### 3rd-Party Software

| Name                         | Author(s)                                        | License                      | Files |
| :--------------------------- | :----------------------------------------------- | :--------------------------- | :---- |
| Easing Functions (Equations) | Robert Penner                                    | 3-Clause BSD License         | [`easings.hpp`](./modules/emergent/include/emergent/math/easings.hpp) |
| FreeType                     | David Turner, Robert Wilhelm, and Werner Lemberg | FreeType License (BSD-style) | [`freetype/*`](./modules/freetype/) |
| Simple DirectMedia Layer     | Sam Lantinga                                     | zlib License                 | [`SDL2/*`](./modules/SDL2/) |

