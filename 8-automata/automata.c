#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 512
#define randnum double

int mesh[N][N];

static inline randnum RNG_16807 () {
	/* using 16807 random number generator */
	/* m = aq+r, q = [m/a], r = m mod a */
	int a = 16807, m = 2147483647, q = 127773, r = 2836;
	static int z = 1; // seed = 1
	int temp;

    temp = a * (z % q) - r * (int)(z / q);
    if (temp >= 0)
        z = temp;
    else
        z = temp + m;
    return (double) z/m;
}

int init_mesh (int length) {
    int count = 0;
    while (count < length) {
        double rand_num = RNG_16807();
        int len = (int)(rand_num * N * N);
        int line = len / N;
        int col = len - line * N;
        if (mesh[line][col] != 1) {
            // fprintf(stdout, "(%d,%d)\n", line, col);
            mesh[line][col] = 1;
            count = count + 1;
        }
    }
    return 0;
}

int print_mesh (FILE *file) {
/* 输出自旋向上的格点 */
    int count = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (mesh[i][j] ==1)
                count = count + 1;
                fprintf(file, "%d, %d\n", i, j);
        }
    }
    return count;
}

int if_up (int line, int col) {
    if (line > 0 && col > 0 && line < N && col < N) {
        if (mesh[line][col] == 1) return 1;
        else return 0;
    }
    return 0;
}

static inline int convert_cell (int line, int col) {
    if ((line == 0 && col != 0) || (line == 0 && col != N - 1) \
    || (line == N - 1 && col != 0) || (line == N - 1 && col != N - 1)) {
        return 0;
    } // 只有三个邻居，不可能能量守恒

    int neighbor_up = if_up(line - 1, col) + if_up(line, col - 1) \
    + if_up(line + 1, col) + if_up(line, col + 1);
    if (neighbor_up == 2) {
        mesh[line][col] = 1 - mesh[line][col];
        return 0;
    } // 有四个邻居

    else if ((line == 0 && col == 0) || (line == 0 && col == N - 1) \
    || (line == N - 1 && col == 0) || (line == N - 1 && col == N - 1)) {
        if (neighbor_up == 1) {
            mesh[line][col] = 1 - mesh[line][col];
            return 0;
        }
        else return 0;
    } // 有两个邻居
}

static inline int convert_odd () {
    int s = 1;
    for (int i = 0; i < N; ++i) {
        s = 1 - s;
        for (int j = s; j < N; j = j + 2) {
            convert_cell(i, j);
        }
    }
    return 0;
}

static inline int convert_even () {
    int s = 0;
    for (int i = 0; i < N; ++i) {
        s = 1 - s;
        for (int j = s; j < N; j = j + 2) {
            convert_cell(i, j);
        }
    }
    return 0;
}

int main (int argc, char **argv) {
    int ratio_up;
    sscanf(argv[1], "%d", &ratio_up);
    int num_up = N * N * ratio_up / 100;
    init_mesh(num_up);

    char folder[10] = "test";
    char ratio[5];
    sprintf(ratio, "%d", ratio_up);
    mkdir(strcat(folder, ratio), 0777);
    
    char tmp[10] = "/t_";
    strcat(folder, tmp);

    // FILE *count_file;
    // count_file = fopen("count", "w+");

    for (int i = 0; i < 10000; ++i) {
        FILE *file;
        char f[20];
        strcpy(f, folder);
        char step[10];
        sprintf(step, "%d", i);
        strcat(f, step);
        file = fopen(f, "w+");

        int count = print_mesh(file);
        fprintf(stdout, "%d\n", count);

        convert_even();
        convert_odd();
        fclose(file);
    }
    // fclose(count_file);
    return 0;
}