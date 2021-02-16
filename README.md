# imstable

## Image rotation/stabilisation library

![CMake](https://github.com/electrodonkey/imstable/workflows/CMake/badge.svg)

Image rotation is a common image processing operation, let's give it a try.
This is mostly an exercise in C++ and Cmake.

## Getting started

On Linux:

```sh
git clone https://github.com/electrodonkey/imstable.git
cd imstable
mkdir build && cd build
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release # or Debug
make
```

On Windows (mingw32-make needs to be installed and the commands should be run from Git Bash):

```sh
git clone https://github.com/electrodonkey/imstable.git
mkdir build && cd build
cmake .. -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=Release # or Debug
make
```

## Open Topics

- [x] reading a PGM (Portable Gray Map)file
- [x] CW90, CCW90, FlipHoriz, FlipVertical
- [x] rotation from pivot point
- [x] bilinear interpolation of pixels
- [] crop
- [] crop to largest rectangle

## Supported file types

- Currently only [ASCII PGM](http://davis.lbl.gov/Manuals/NETPBM/doc/pgm.html)/[PGMA](https://people.sc.fsu.edu/~jburkardt/data/pgma/pgma.html)
- Will be extended to other file types

## System requirements  

- Doxygen
- CMake > 3.11
- GCC toolchain

## Assumptions

- All PGM files have only one comment on the 2nd line
- Currently only (P2) PGMA files are supported
