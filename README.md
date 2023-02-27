# ASCII Art Generator

A utility for generating the ASCII art equivalent of a PNG or JPEG image.

### Building `asciigen`

To build this project you'll need the following tools and libraries installed
on your system:

* CMake3.11+
* C++ compiler supporting C++17 features
* libpng developer libraries
* libjpeg developer libraries
* zlib developer libraries
* Boost version 1.76.0

To build the project, change directory to the [scripts](scripts) directory and
run `build.sh`:
```
./build.sh
```

A successful build will install the `asciigen` binary to the `bin` directory
under the project root.

### Running `asciigen`

`asciigen` operates like most commandline utilities. The program usage is as
follows:
```
asciigen [OPTIONS]... IMAGE FILE
```
where `IMAGE` is an input PNG or JPEG file and `FILE` is the path to the ASCII
output file. You can run `asciigen` with the `-h` option to get a full list of
program options.

### Running `asciigen` Under Docker

It might be a bit cumbersome to install all the tools listed in the
build section of this README. If you have Docker installed on your system,
you can build an image or download a pre-built image that will allow you to
run `asciigen` without the need to build locally.

To run `asciigen` from within a docker container, run the `demo.sh` script
under the [scripts](scripts) directory. Before executing the script, edit the
`LOCAL_IMAGE_DIR` variable to point to a directory on your host machine
containing the image(s) you would like to generate art for. This
`LOCAL_IMAGE_DIR` directory will be mapped to the `/mnt` directory within the
container.

To run the `asciigen` container:
```
./demo.sh
```

From within the container you can take input and produce output that appears
on your host machine with a command similar to the following:
```
asciigen /mnt/cool_picture.png /mnt/cool_picture.ascii
```
On the host machine, you will see `cool_picture.ascii` popup under the directory
you specified for `LOCAL_IMAGE_DIR` earlier.
