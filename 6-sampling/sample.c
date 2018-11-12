#include <stdio.h>
#include <math.h>

#define N 1000 // 随机数总数
#define PI 3.141592653589793

int RNG_16807(double random[], int M) {
	/* 16807随机数产生器 */
	/* m = aq+r, q = [m/a], r = m mod a */
	int a = 16807, m = 2147483647, q = 127773, r = 2836;
	int z = 1; // seed = 1
	int temp;

	for (int i = 0; i < M; i++) {
		temp = a * (z % q) - r * (int)(z / q);
		if (temp >= 0)
			z = temp;
		else
			z = temp + m;
		random[i] = (double) z/m;
	}
	return 0;
}


int main() {

	double random_numbers[2 * N], cost[N], sint[N], phi[N], x[N], y[N], z[N];
	// cost == cos(theta), sint == sin(theta)
	RNG_16807(random_numbers, 2 * N);

	for (int i = 0; i < N; i++) {
		// 抽样方法解释见报告
		cost[i] = 1 - 2 * random_numbers[2 * i];
		sint[i] = sqrt(1 - cost[i] * cost[i]);
		phi[i] = 2 * PI * random_numbers[2 * i + 1];

		x[i] = sint[i] * cos(phi[i]);
		y[i] = sint[i] * sin(phi[i]);
		z[i] = cost[i];
		fprintf(stdout, "%lf, %lf, %lf\n", x[i], y[i], z[i]);
	}
	return 0;
}
