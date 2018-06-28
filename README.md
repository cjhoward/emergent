# Emergent

Emergent is a C++ framework for real-time 3D applications.

## Download

Use Git to download the Emergent repository and its submodules:

	git clone --recursive https://github.com/cjhoward/emergent.git emergent

## Building and Installation

Emergent uses a CMake build system to configure, build, and install Emergent and its dependencies. Ensure CMake is installed before proceeding.

### Configuration

The following basic CMake configuration options are available:

| Option                       | Description                                                                     |
| ---------------------------- | ------------------------------------------------------------------------------- |
| `BUILD_DOCS:BOOL=OFF`        | Build the API reference docs.                                                   |
| `BUILD_EXAMPLES:BOOL=ON`     | Build the example programs.                                                     |
| `BUILD_STATIC:BOOL=OFF`      | Build a static version of the library.                                          |
| `CMAKE_BUILD_TYPE:STRING=`   | Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel. |
| `CMAKE_INSTALL_PREFIX:PATH=` | Install path prefix, prepended onto install directories.                        |

For a full list of advanced CMake configuration options, run the command `cmake .. -LAH` from the `build` directory.

### Building on GNU/Linux

Building on GNU/Linux requires GCC, G++, and GNU Make. Open a command prompt in the `build` directory then run the following commands:

	cmake .. -G "Unix Makefiles" -DBUILD_DOCS=OFF -DBUILD_EXAMPLES=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=<...>
	cmake --build .

### Building on Windows

Building on Windows requires Visual Studio 2017. Open the Visual Studio Native Tools Command Prompt in the `build` directory then run the following commands:

	cmake .. -G "NMake Makefiles" -DBUILD_DOCS=OFF -DBUILD_EXAMPLES=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=<...>
	cmake --build .

### Installation

Run the following command to install Emergent and its dependencies in the directory specified by the `CMAKE_INSTALL_PREFIX` option:

	cmake --build . --target install

## Usage

To use Emergent in a CMake-built application, add the following to its `CMakeLists.txt`:

	set(emergent_DIR ${EMERGENT_INSTALL_PREFIX}/lib/cmake/emergent)
	find_package(emergent REQUIRED CONFIG)
	add_executable(${EXECUTABLE} ${SOURCE_FILES})
	target_link_libraries(${EXECUTABLE} emergent)

`${EMERGENT_INSTALL_PREFIX}` is the location at which Emergent was installed, `${EXECUTABLE}` is your application's executable name, and `${SOURCE_FILES}` is a list of your application's source files.

## License

The source code for Emergent is licensed under the GNU General Public License, version 3. See [`COPYING`](./COPYING) for details.

Documentation text and assets for Emergent are licensed under a [Creative Commons Attribution-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-sa/4.0/).
