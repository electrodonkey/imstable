# imstable

Image rotation library

![CMake](https://github.com/electrodonkey/imstable/workflows/CMake/badge.svg)

Image rotation is a common image processing operation.
It can be solved with the image rotation matrix (https://en.wikipedia.org/wiki/Rotation_matrix)

## Open Topics

- reading a PGM (Portable Gray Map)file
- crop to largest rectangle
- interpolation of pixels (bilinear, cubic)


Reading in a PGM file
---------------------

The general strategy is:

- open the image file 
- read in the first line of the header and check it contains 'P2'.
- read in the second line containing the two integers specifying the size
- check if its a comment line - while the line starts with #, read in the next line
- extract the two integers that specify the size of the image from that line
- read in the last line of the header and check it contains 255.

- allocate a 2D array the size of the image
- read in the pixel values one by one and put them into appropriate slot of 
  the array.

/* assuming width and height are integers with the image's dimensions */
		int hwidth = width / 2;
		int hheight = height / 2;
        double sinma = sin(-angle);
		double cosma = cos(-angle);
for(int x = 0; x < width; x++) {
	for(int y = 0; y < height; y++) {
		
		int xt = x - hwidth;
		int yt = y - hheight;
		
		int xs = (int)round((cosma * xt - sinma * yt) + hwidth);
		int ys = (int)round((sinma * xt + cosma * yt) + hheight);

		if(xs >= 0 && xs < width && ys >= 0 && ys < height) {
			/* set target pixel (x,y) to color at (xs,ys) */
		} else {
			/* set target pixel (x,y) to some default background */
		}
	}
}

## Requirements 
- Doxygen
- CMake
- GCC toolchain


# How to build 

```sh
mkdir build
cd build
cmake .. -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=Debug // or Release
make
```

## Assumptions
- All PGM files have only one comment on the 2nd line
- We open only ASCII (P2) PGM files
