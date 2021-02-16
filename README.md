# imstable

Image rotation/stabilisation library

![CMake](https://github.com/electrodonkey/imstable/workflows/CMake/badge.svg)

Image rotation is a common image processing operation, let's give it a try.

## Getting started

```sh
https://github.com/electrodonkey/imstable.git
mkdir build && cd build
cmake .. -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=Release # or Debug
make
```

## Open Topics

- [x] reading a PGM (Portable Gray Map)file
- [x] CW90, CCW90, FlipHoriz, FlipVertical
- [] rotation from pivot point
- [] interpolation of pixels (bilinear, cubic)
- [] crop to largest rectangle


## Supported file types

- Currently only [ASCII PGM](http://davis.lbl.gov/Manuals/NETPBM/doc/pgm.html)/[PGMA](https://people.sc.fsu.edu/~jburkardt/data/pgma/pgma.html)
- Will be extended to other file types

## Requirements 

- Doxygen
- CMake
- GCC toolchain

## Assumptions

- All PGM files have only one comment on the 2nd line
- We open only ASCII (P2) PGM files
