# imstable

Image rotation library

Omage rotation is a common image processing operation.
It can be solved with the image rotation matrix (https://en.wikipedia.org/wiki/Rotation_matrix)

## Open Topics

- crop to largest rectangle
- interpolation of pixels (bilinear, cubic)


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