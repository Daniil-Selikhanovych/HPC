nvcc -o blurring.o blurring.cu
./blurring.o edge
./blurring.o sharpen
./blurring.o gaussian
nvcc -o median_blurring.o median_blurring.cu
./median_blurring.o