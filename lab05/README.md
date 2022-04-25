# Report on Lab 05

## Task 1
The program take 1 input: the RGB image path.
```shell
./task1/build/main image.jpg
```

To find the crack in the street I use the threshold method because the cracks are darker than the asphalt. The problem is that there are a lot of noise due to the texture of the asphalt, so I preprocessed the image blurring it and applying the log transform. 


## Task 2
The program take 1 input: the RGB image path.
```shell
./task2/build/main image.jpg
```
For the second task I use clustering with kmeans. The pixels are represented by a 5-dimensional vector:

- `x` position
- `y` position
- `blue` value
- `green` value
- `red` value

## Task 3
The program take 1 input: the RGB image path.
```shell
./task3/build/main image.jpg
```

I use the `cv::inRange()` function for extracting the yellow pixels of the shirts. I converted the BGR image to the HSV beacuse is easier to identify the colors.
