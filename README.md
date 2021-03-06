# imstable

![CMake](https://github.com/electrodonkey/imstable/workflows/CMake/badge.svg)

## About

Imstable is an image rotation/stabilisation library.
Image rotation is a common image processing operation, let's give it a try.
This is mostly an exercise in C++ and Cmake in my attempt to become better at them.

## Demo

Given an input PGMA image, a rotation angle, and coordinates for the crop rectangle, using imstable you can get the following output:

Command: 
```bash
./imstable_demo.exe -f ../assets/lena.ascii.pgm -o rotate -a +20 -cx 200 -cy 200 -ch 200 -cw 200
```

Input image:

<img src="documentation/images/input.png" width="200">

Output image:

<img src="documentation/images/output.png" width="200">

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
- [x] crop
- [ ] crop to largest rectangle

## Supported file types

- Currently only [ASCII PGM](http://davis.lbl.gov/Manuals/NETPBM/doc/pgm.html)/[PGMA](https://people.sc.fsu.edu/~jburkardt/data/pgma/pgma.html)
- Will be extended to other file types

## Viewing PGMA images

- Irfanview on Windows
- Imagemagick on Linux and Windows

## System requirements  

- CMake >= 3.19
- GCC toolchain (8.1.0 used)
- Doxygen (to generate documentation)

## Assumptions

- All PGM files have only one comment on the 2nd line
- Currently only (P2) PGMA files are supported
