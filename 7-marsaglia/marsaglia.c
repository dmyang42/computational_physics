#include <stdio.h>
#include <math.h>

#define N 10000   // the amount of random numbers
#define PI 3.141592653589793

int RNG_16807(double random[], int M) {
	/* 16807随机数生成器 */
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
		random[i] = (double)z / m;
	}
	return 0;
}

int main() {
	/* marsaglia抽样方法 */
	double random_numbers[2 * N], u[N], v[N], r2[N], x[N], y[N], z[N];
	RNG_16807(random_numbers, 2 * N); // 随即抽样

	for (int i = 0; i < N; i++) {
		u[i] = random_numbers[2 * i] * 2 - 1; // u [-1,1]
		v[i] = random_numbers[2 * i + 1] * 2 - 1; // v [-1,1]
		r2[i] = u[i] * u[i] + v[i] * v[i]; // r2 = r^2
		
		x[i] = 2 * u[i] * sqrt(1 - r2[i]);
		y[i] = 2 * v[i] * sqrt(1 - r2[i]);
		z[i] = 1 - 2 * r2[i];
		printf("%lf, %lf, %lf\n", x[i], y[i], z[i]);
	}
	return 0;
}
