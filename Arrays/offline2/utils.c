#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265358979323846

// Function to generate a normally distributed random number
double generate_normal(double mu, double sigma) {
  double U1 = (double)rand() / (double)RAND_MAX;
  double U2 = (double)rand() / (double)RAND_MAX;
  double X1 = sqrt(-2 * log(U1)) * cos(2 * PI * U2);
  return mu + sigma * X1;
}

void populate_array_gaussian(double *array, int size, double mu, double sigma, unsigned int seed) {
    srand(seed);
    for (int i = 0; i < size; i++) {
        array[i] = generate_normal(mu, sigma);
    }
}

void populate_array_uniform(double *array, int size, double min, double max, unsigned int seed) {
    srand(seed);
    for (int i = 0; i < size; i++) {
        array[i] = min + (double)rand() / ((double)RAND_MAX / (max - min));
    }
}