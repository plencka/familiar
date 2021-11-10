# Familiar
TODO: College project.. thing.

[![.github/workflows/build.yml](https://github.com/plencka/Familiar/actions/workflows/build.yml/badge.svg)](https://github.com/plencka/Familiar/actions/workflows/build.yml)

# Installation
## Compilation using [Docker](https://www.docker.com/)

Project contains script files named `docker-build`. It builds the image and creates temporary container, to compile and extract executables into the `builds` folder, put into the project's root directory. 

>This should always use the newest version of image. If the changes aren't reflected in the binary files, make sure docker recreates last compilation steps or if the created container uses latest version.

To get started, simply run it.

## Compilation on host machine
Make sure you have conan and cmake installed before reproducing provided steps. 

This project uses [Conan](https://docs.conan.io/en/1.35/introduction.html) to install dependencies. If you're using different package manager, you can reference the `conanfile.txt` file for requirements and the configuration.

### Installing and building

> You might want to update remote to use the new [ConanCenter](https://conan.io/center/) first. The default configuration as of time of writing is deprecated, which causes errors during installation.
You can do that through command line:
>```console
>conan remote update conan-center https://center.conan.io
>```

1. First, create your `build` directory. Following commands need to be run from it.
```console
mkdir build
cd build
```

2. Install dependencies using conan. This command needs to be rerun each time dependencies change.
```console
conan install ..
```

3. Generate and build cmake files. You can specify compiler used in generation with the `-G` flag of the first command.
>#### Windows:
>```console
>cmake ..
>cmake --build . --config Release
>```

>#### Linux, Mac:
>```console
>cmake .. -DCMAKE_BUILD_TYPE=Release
>cmake --build .
>```

> You might want to develop in Debug mode. For that, you need to change dependencies to use debug versions of libraries.

## Development
To develop, you need to link the libraries to your IDE software.

### Setting up Visual Studio's IntelliSense
1. Create `vsbuild` directory. Destination is defined in `CMakeSettings.json` and you need to adjust paths there if you want to change the build location. Following commands need to be run from it.
```console
mkdir vsbuild
cd vsbuild
```

2. Install dependencies using conan.
```console
conan install ..
```

3. You can use the `Generate Cache` option, which appears when right-clicking CMakeLists.txt. You can also be prompted to do it with notification box. Otherwise you need to link external libraries manually.
