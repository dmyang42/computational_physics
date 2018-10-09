#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#define RANGE 2048
#define DISTANCE 100

int particle_set[RANGE][RANGE];
int center = (int) RANGE / 2;
int dynamic_range;

int dla_init () {
	/* 初始化网格 */
	int initial_range = 100;
	particle_set[center][center] = 1;
	fprintf(stdout, "%d, %d\n", center, center);
	dynamic_range = initial_range;
}

static inline int dla_dynamic_border (int max) {
	/* 通过当前团簇偏离凝聚中心最远的距离计算动态边界 */
	dynamic_range = 2 * max + DISTANCE;
}

static inline int dla_generate (int *pY, int *pX, int *count) {
	/* 在动态边界范围内随机生成粒子 */
	int low = center - dynamic_range / 2;
	int high = center + dynamic_range / 2;

	do {
        *pX = rand() % dynamic_range + low;
        *pY = rand() % dynamic_range + low;
    } while (particle_set[*pY][*pX] == 1);

	(*count)++;
	return 0;
}

static inline int dla_walk (int *pY, int *pX) {
	/* 粒子自由移动 */
	int low = center - dynamic_range / 2;
	int high = center + dynamic_range / 2;

    int dir = rand() % 8;
    switch (dir) {
		case 0: // 右移
			(*pX)++;
			break;
		case 1: // 左移
			(*pX)--;
			break;
		case 2: // 下移
			(*pY)++;
			break;
		case 3: // 上移
			(*pY)--;
			break;
		case 4: // 右下
			(*pX)++;
			(*pY)++;
			break;
		case 5: // 右上
			(*pX)++;
			(*pY)--;
			break;
		case 6: // 左下
			(*pX)--;
			(*pY)++;
			break;
		case 7: // 左上
			(*pX)--;
			(*pY)--;
			break;
		default:
			break;
    }

    /* 超出范围处理：从另一侧出来 */
	/* 如超出上边界，则粒子移动到下边界相应位置 */
    if (*pX > high) *pX = low;
	else if (*pX < low) *pX = high;

    if (*pY > high) *pY = low;
    else if (*pY < low) *pY = high;
    
	return 0;
}

static inline bool is_adjacent (int pY, int pX) {
	/* 判断是否附着在团簇上 */
	/* 返回TRUE表示附着， FALSE则不然 */
    int xp, yp;
    xp = pX + 1;
    if (particle_set[pY][xp] == 1) return true;

    yp = pY + 1;
    if (particle_set[yp][xp] == 1) return true;
    if (particle_set[yp][pX] == 1) return true;

    yp = pY - 1;
    if (particle_set[yp][xp] == 1) return true;
    if (particle_set[yp][pX] == 1) return true;

    xp = pX - 1;
    if (particle_set[yp][xp] == 1) return true;
    if (particle_set[pY][xp] == 1) return true;

    yp = pY + 1;
    if (particle_set[yp][xp] == 1) return true;

    return false;
}

static inline int which_max(int x, int y, int z) {
	/* 判断三个数中最大数 */
	int temp=0;
	if (x >= y) 
		temp = x;
	else
		temp = y;
	if (z >= temp)
		return z;
	else
		return temp;
}

int main (int argc, char **argv) {
	int count = 0; // 粒子数计数
	int max = 0; // 用于动态边界
	int particle_num;
	// FILE *SandboxFile;
	sscanf(argv[1], "%d", &particle_num);

	/* 初始化 */
    // SandboxFile = fopen("./test_sandbox","w");
    srand((unsigned) time(NULL));
    dla_init();

	/* 主循环 */
	while (count < particle_num && abs(RANGE-dynamic_range) > DISTANCE) {
		dla_dynamic_border(max); // 更新动态边界
		// fprintf(SandboxFile, "%d, %d\n", count, max+1);

		int pY, pX;
		dla_generate(&pY, &pX, &count); // 生成粒子
		
		while (!is_adjacent(pY, pX)) {
			dla_walk(&pY, &pX); // 循环粒子移动
		}
		particle_set[pY][pX] = 1; // 附着在团簇上
		fprintf(stdout, "%d, %d\n", pY, pX);
		
		max = which_max(max, abs(pX-center), abs(pY-center)); // 更新max
	}
	fprintf(stderr, "final dynamic border: %d\n", max);
	fprintf(stderr, "total particles: %d", count);
	
	return 0;
}