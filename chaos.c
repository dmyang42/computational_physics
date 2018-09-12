#include <stdio.h>
#include <math.h>

#define PI 3.1415926535897932
#define ITERATION_NUM 100000 // Iteration times for each lambda
#define OUTPUT_NUM 200 // Output the last 100 data for each lambda
#define ERROR 0.000000001

int simple_traverse(double x_start, double lambda_start, double lambda_end, double lambda_update) {
    /*
    this function iterates for each lambda for ITERATION_NUM times
    and will record the last OUTPUT_NUM data
    */
    double x = x_start;

    double t;
    int record_num = ITERATION_NUM - OUTPUT_NUM;
    for (double lambda = lambda_start; lambda < lambda_end - ERROR; lambda += lambda_update) {
        for (int i = 0; i < ITERATION_NUM; i = i + 2) {
            t = lambda * sin(PI*x);
            x = lambda * sin(PI*t);
            if (i >= record_num) {
                fprintf(stdout, "%.8f, %.15lf\n", lambda, t);
				fprintf(stdout, "%.8f, %.15lf\n", lambda, x);
			}
		}
        x = 0.11;
	}
    return 0;
}

int fast_traverse(double x_start, double lambda_start, double lambda_end, double lambda_update) {
    /*
    this function can go through 'lambda' faster than 'simple_traverse'
    it will neglect the rest data once it reaches a period
    including stable point
    */
    double x = x_start;

    double t, d;
    int record_num = ITERATION_NUM - OUTPUT_NUM;
	for (double lambda = lambda_start; lambda < lambda_end; lambda += lambda_update) {
        for (int i = 0; i < ITERATION_NUM; i = i + 2) {
			t = lambda * sin(PI*x);
            x = lambda * sin(PI*t);
            d = t - x;
            if (fabs(d) < ERROR) {
                // t == x, record and break
				fprintf(stdout, "%.8f, %.15lf\n", lambda, x);
                break;
            }
            if (i >= record_num) {
                // record the last record_num data
                double ref = x;
                for (int j = 1; i < ITERATION_NUM; i = i + 2, ++j) {
                    // expand the loop, optimization method
                    fprintf(stdout, "%.8f, %.15lf\n", lambda, x);
                    fprintf(stdout, "%.8f, %.15lf\n", lambda, t);
        			t = lambda * sin(PI*x);
                    x = lambda * sin(PI*t);
                }
			}
		}
        x = 0.11;
	}
    return 1;
}

int main(int argc, char **argv) {
    /*
     * Parameters
     */
    FILE *fp = NULL;
    double lambda_start;
    double lambda_end;
    double lambda_update;
    double x;

    /*
     * Hardcode here
     */
    // double lambda_start = 0.7198;
    // double lambda_end = 0.7200;
    // double lambda_update = 0.00000001;
    // double x = 0.11;

    /*
     * User input to replace hardcode
     */
    sscanf(argv[1], "%lf", &lambda_start);
    sscanf(argv[2], "%lf", &lambda_end);
    sscanf(argv[3], "%lf", &lambda_update);
    sscanf(argv[4], "%lf", &x);

    /*
     * Iteration, choose one traverse method
     * Simple traverse: for short range and period-doubling bifurcation points
     * Fast traverse: for long range
     */
    simple_traverse(x, lambda_start, lambda_end, lambda_update);
    // fast_traverse(x, lambda_start, lambda_end, lambda_update);

	return 0;
}
