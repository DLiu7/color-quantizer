#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// Function to calculate the Euclidean distance between two pixels
float squareDist(float *a, float *b)
{
    return ((a[0] - b[0]) * (a[0] - b[0]) + 
            (a[1] - b[1]) * (a[1] - b[1]) + 
            (a[2] - b[2]) * (a[2] - b[2]));
}

void kmeans_clustering(float *pixels, int num_pixels, int num_centroids, int max_iters, int seed, float *centroids, int *labels)
{

    /*
    float* pixels: The input array of pixels, each pixel is a 3 byte RGB value
    int num_pixels: the number of pixels in the above array
    int num_centroids: the number of centroids, which is the same as the number of pixels in the colormap.
    int max_iters: maximum number of iterations for the K-means algorithm
    int seed: seed to use for the srand() function. Use srand()/rand()
    float* centroids: array of 3 byte centroids.
    int* labels: The color in the map for each pixel - one byte for each pixel
    */

    // Seed the random number generator
    srand(seed);

    // Randomly initialize the centroids by picking random pixels from the input array.
    // Centroids are not accurate, but they are good enough to start the K-means algorithm.
    for (int i = 0; i < num_centroids; i++)
    {
        int idx = rand() % num_pixels;
        centroids[i * 3] = pixels[idx * 3];          // R
        centroids[i * 3 + 1] = pixels[idx * 3 + 1];  // G
        centroids[i * 3 + 2] = pixels[idx * 3 + 2];  // B

        // Each centroid is a single RGB
        // Labels contains the index of the centroid that is closest to the pixel
        // RGB pixels (3 floats) are compressed to the centroids (index that has 3 floats)
    }

    // Allocate memory for the sums and counts
    // Sums will store the sum of RGB values for each centroid
    // Counts will store the number of pixels assigned to each centroid
    float *sums = (float *)malloc(num_centroids * 3 * sizeof(float));
    int *counts = (int *)malloc(num_centroids * sizeof(int));

    // Run the K-means algorithm for max_iters iterations
    // Gets closer to the actual centroids with each iteration
    for (int iter = 0; iter < max_iters; iter++)
    {
        // CLeans the sums and counts
        memset(sums, 0, num_centroids * 3 * sizeof(float));
        memset(counts, 0, num_centroids * sizeof(int));

        // Assign each pixel to the closest centroid by finding the minimum distance
        for (int i = 0; i < num_pixels; i++)
        {
            // Find the distance of the pixel from the first centroid
            // Is not the actual minimum distance
            float min_dist = squareDist(&pixels[i * 3], &centroids[0]);

            // Index of the closest centroid
            int min_idx = 0;

            // Find the closest centroid to the pixel by comparing distances
            for (int j = 1; j < num_centroids; j++)
            {
                float dist = squareDist(&pixels[i * 3], &centroids[j * 3]);
                if (dist < min_dist)
                {
                    min_dist = dist;
                    min_idx = j;
                }
            }

            // Update the sums and counts & stores the index of the closest centroid into the labels array
            labels[i] = min_idx;
            sums[min_idx * 3] += pixels[i * 3];
            sums[min_idx * 3 + 1] += pixels[i * 3 + 1];
            sums[min_idx * 3 + 2] += pixels[i * 3 + 2];
            counts[min_idx]++;
        }

        // Compresses the pixels to the centroids

        // Update the centroids by taking the mean of the pixels assigned to them
        for (int i = 0; i < num_centroids; i++) {
            if (counts[i] > 0) {
                centroids[i * 3] = sums[i * 3] / counts[i];
                centroids[i * 3 + 1] = sums[i * 3 + 1] / counts[i];
                centroids[i * 3 + 2] = sums[i * 3 + 2] / counts[i];
            }
        }
    }

    free(sums);
    free(counts);
}