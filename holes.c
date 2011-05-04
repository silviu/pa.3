#include <stdio.h>
#include <stdlib.h>

int** alloc_mat(int n, int m)
{
	int i;
	
	int** ret = (int**) malloc(n * sizeof(int*));
	if (NULL == ret) {
		fprintf(stderr, "malloc failure in \"alloc(int, int)\"\n");
		return NULL;
	}
	
	for (i = 0; i < n; i++) {
		ret[i] = (int*) malloc(m * sizeof(int));
		if (NULL == ret[i]) {
			fprintf(stderr, "malloc failure in \"alloc(int, int)\"\n");
			return NULL;
		}
	}
	
	return ret;
}

void free_mat(int** mat, int n, int m)
{
	int i;
	for (i = 0; i < n; i++)
		free(mat[i]);
	free(mat);
}

int** read_map(int* n, int* m)
{
	int i, j;
	char c;
	
	scanf("%d %d\n", n, m);
	int** map = alloc_mat(*n, *m);
	
	if (NULL == map)
		return NULL;
	
	for (i = 0; i < *n; i++) {
		for (j = 0; j < *m; j++) {
			scanf("%c", &c);
			// there is a good road
			if (c == '.')
				map[i][j] = 1;
			// there is a hole in the rod
			else
				map[i][j] = 0;
		}
		scanf("\n");
	}
	
	return map;
}

void print_map(int** map, int n, int m)
{
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++)
			printf("%d ", map[i][j]);
		printf("\n");
	}
}

int main()
{
	int n, m, **map = NULL;
	
	map = read_map(&n, &m);
	if (NULL == map)
		return EXIT_FAILURE;
	
	print_map(map, n, m);
	
	free_mat(map, n, m);	
	return 0;
}
