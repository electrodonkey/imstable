# imstable

Image rotation library

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

- reading a PGM (Portable Gray Map)file -> done
- CW90, CCW90, FlipHoriz, FlipVertical -> done
- interpolation of pixels (bilinear, cubic)
- crop to largest rectangle -> future


# Supported file types

- Currently only [ASCII PGM](http://davis.lbl.gov/Manuals/NETPBM/doc/pgm.html)/[PGM](https://people.sc.fsu.edu/~jburkardt/data/pgmb/pgmb.html)

## Requirements 
- Doxygen
- CMake
- GCC toolchain

## Assumptions
- All PGM files have only one comment on the 2nd line
- We open only ASCII (P2) PGM files
