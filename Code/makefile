CC = gcc
CFLAGS = -Wall -Wextra -O3 -fPIC -std=c99
LDFLAGS = -shared -lm
TARGET = libkernel.so
SRC = kernel.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $@

test: all
	python3 24Bit.py input.png output_image_Py.png output_image_C.png colormap_Py.txt colormap_C.txt --seed 214 --num_centroids 256 --max_iters 3

clean:
	rm -f $(TARGET)

.PHONY: all clean test