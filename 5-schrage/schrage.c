#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#define N 1000000   // the amount of random number to generate
#define START "START"
#define END "END"

double random_numbers[N];

int print_pair (FILE *fp) {
	for (int i = 0; i < N - 1; ++i) {
		fprintf(fp, "%.15lf, %.15lf\n", random_numbers[i], random_numbers[i + 1]);
	}
	return 0;
}

int schrage_generate (int seed) {
	/* 
	 * m = a * q + r
	 * q = [m / a]
	 * r = m mod a 
	 */
	int a = 16807, b = 0, m = 2147483647, q = 127773, r = 2836;
	int temp;
	int z = seed;
	random_numbers[0] = (double)z / m;

	for (int i = 1; i < N; ++i) {
		temp = a * (z % q) - r * (int)(z / q);
		if (temp >= 0)
			z = temp;
		else
			z = temp + m;
		random_numbers[i] = (double)z / m;
	}
	return 0;
}

int fibonacci_generate (int seed) {
	
	return 0;
}

int kth_order_moment (int start_order, int end_order, FILE *fp) {
	for (int j = start_order; j <= end_order; ++j) {
		int	M = pow(10, j);
		fprintf(fp, "N = %d\n", M);
		fprintf(fp, "%5s%20s%20s%20s\n", "k", "kth moment", "1 / 1 + k", "deviation");
		for (int k = 1; k <= 5; ++k) {
			double k_order_sum = 0;
			double exact_value = 1.0 / (1 + k);
			for (int i = 0; i < M; ++i) {
				k_order_sum += pow(random_numbers[i], k);
			}
			double k_moment = k_order_sum / M;
			double deviation = fabs(k_moment - exact_value);
			fprintf(fp, "%5d%20.15lf%20.15lf%20.15lf\n", k, k_moment, exact_value, deviation);
		}
	}
	return 0;
}

int correlation(FILE *fp) {
	for (int l = 0; l < 1000; ++l) {
		double Sum = 0, Related_Sum = 0, Square_Sum = 0, Mean, RMS, Related_Mean;
		double Cor_Coef;
		for (int i = 0; i < N; ++i) {
			Sum += random_numbers[i];
			Square_Sum += random_numbers[i] * random_numbers[i];
		}
		for (int i = 0; i < N - l; ++i) {
			Related_Sum += random_numbers[i] * random_numbers[i+l];
		}
		Mean = Sum / N;
		RMS = Square_Sum / N;
		Related_Mean = Related_Sum / N;
		Cor_Coef = (Related_Mean - Mean * Mean) / (RMS - Mean * Mean);
		fprintf(fp, "%d, %lf\n", l, Cor_Coef);
	}
	return 0;
}

int increment () {
	/* 测试随机数序列中连续三个随机数是递增的的比重 */
	int i = 1;	
	int count = 0;
	while (i < N - 1) {
		double left = random_numbers[i] - random_numbers[i - 1];
		double right = random_numbers[i + 1] - random_numbers[i]; 
		if (left > 0 && right > 0) {
			i = i + 1;
			count = count + 1;
		}
		else if (right > 0)
			i = i + 1;
		else
			i = i + 2;
	}
	return count;
}


int file_name (char *seed, ...) {
	va_list file_list;
	va_list tmp;
	va_start(file_list, seed);
	va_copy(tmp, file_list);
	while (strcmp(va_arg(tmp, char*), END) != 0) {
		strcat(va_arg(file_list, char*), seed);
	}
	va_end(tmp);
	va_end(file_list);
	return 0;
}

int main (int argc, char **argv) {
	int z;
	FILE *file_pair;
	FILE *file_kth_order;
	FILE *file_correlation;
	char f1[20] = "schrage_";
	char f2[20] = "kth_order_";
	char f3[20] = "correlation_";
	char seed[10];

	sscanf(argv[1], "%d", &z); // seed
	sprintf(seed, "%d", z);
	file_name(seed, f1, f2, f3, END);
	file_pair = fopen(f1, "w+");
	file_kth_order = fopen(f2, "w+");
	file_correlation = fopen(f3, "w+");

	schrage_generate(z);
	print_pair(file_pair);
	kth_order_moment(3, 5, file_kth_order); // 1000, ..., N
	correlation(file_correlation);
	fprintf(stderr, "%.4f", (float)increment() / N);

	return 0;
}
