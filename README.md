# CSC418-final-image
The project is based on code I write in assignment3. New files are added and some odd files won't be used.<br>
The project is about blurring the background image using `gaussian-blur` (the algorithm used here is commented in the code gaussian-blur.cpp). And use chroma algorithm 
to filter out the original image's background (see chroma.ppm below). Then I convert the chroma image from rgb to rgba, the reason is to make the background to betransparent.
So I can put the chroma image over the blurred background image to make a brand new image. `rgb_to_rgba` and `over` function used here are inherented from our assignment 1.<br>

## work I have done (new file)
`src/gaussion_blur.cpp`<br>
This file is used to do gaussion blur on the background image. The algorithm is based on [gaussion_blur](http://blog.ivank.net/fastest-gaussian-blur.html)

`src/chroma.cpp` <br>
This file is used to filter out the background color in the cat picture. It is implemented based on algorithm [here](http://gc-films.com/chromakey.html)

`src/ppm.cpp` <br>
This file is used to wite and read ppm file.

`src/over.cpp` <br>
This file is used to add the cat to the blurred background.

`src/rgb_to_rgba.cpp`<br>

There are also files I have modified (main.cpp etc.)
