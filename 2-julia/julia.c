#include <stdio.h>
#include <math.h>
 
#define MAX 2 
#define STEP 0.001
#define ZERO 0.000000001
#define RADIUS 300

int is_julia(double x_0, double y_0, double a, double b, int num) {
	/*
	 * this func will return 1 if the point belongs to Julia set
	 * and will return 0 if dont
	 */

	double x = x_0;
	double y = y_0;
	double z_sq;

	double tmp;
	for (int i = 0; i < num; ++i) {   
		tmp = (x * x - y * y) + a; // iteration equation
		y = 2 * x * y + b;
		x = tmp;

		z_sq = x * x + y * y; // z^2 = x^2 + y^2
		if (z_sq > RADIUS || z_sq < ZERO) {      
			return 0;     
		}
	}
	return 1;
}

int main(int argc, char **argv) {
	
	double a, b; 
	int num;
	int count = 0; // count the number of points in Julia set

	sscanf(argv[1], "%lf", &a);
	sscanf(argv[2], "%lf", &b);
	sscanf(argv[3], "%d", &num);

	for (double x_0 = 0 - MAX; x_0 < MAX; x_0 = x_0 + STEP) {
		for (double y_0 = 0 - MAX; y_0 < MAX; y_0 = y_0 + STEP) {
			if (is_julia(x_0, y_0, a, b, num)) { 
				fprintf(stdout, "%f, %f\n", x_0, y_0);				
				count++;
			}
		}
	}

	fprintf(stderr, "%d points in total\n", count);

	return 0;
}