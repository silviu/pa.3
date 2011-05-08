#include <stdio.h>
#include <stdlib.h>

#define HOLE 0
#define ROAD 1
int NO = 1;
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
	*n = *n + 1;
	*m = *m + 1;
	int** map = alloc_mat(*n, *m);
	
	if (NULL == map)
		return NULL;
	
	for (i = 1; i < *n; i++) {
		for (j = 1; j < *m; j++) {
			scanf("%c", &c);
			// there is a good road
			if (c == '.')
				map[i][j] = ROAD;
			// there is a hole in the rod
			else {
				map[i][j] = HOLE;
				map[i][0]++;
				map[0][j]++;
			}
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

int has_vertical_neighbours(int** map, int i, int j, int n)
{
	if (i - 1 > 0 && map[i - 1][j] != ROAD)
		return 1;
	
	if (i + 1 < n && map[i + 1][j] != ROAD)
		return 1;
	
	return 0;
}

int next_is_hole(int** map, int i, int j, int n, int m)
{
	if (j < m)
	if( map[i][j] == HOLE)
		return 1;
	
	return 0;
}

void cover_line_of_isolated(int** map, int start_i, int start_j, int n, int m, int NO)
{
	int i = start_i;
	int j = start_j;
	
	while(next_is_hole(map, i, j, n , m))
	{
		map[i][j] = NO;
		// calculate the number of holes left on this column
		map[0][j]--;
		j++;
	}
	
	// calculate the number of holes left on this line
	map[start_i][0] -= (j - start_j);
	NO++;
}

int has_no_line_neighbours(int** map, int i, int j, int n , int m)
{
	if (j + 1 >= m)
		return 1;
	
	if (map[i][j + 1] != HOLE)
		return 1;
	
	return 0;
}

void isolated_on_line(int** map, int n, int m)
{
	int i, j;
	for (i = 1; i < n; i++) {
		// if there are no holes on this line
		// go to next line
		if (map[i][0] == 0)
			continue;
		
		int saved_coords = 0;
		int start_i = -1, start_j = -1;
		
		for (j = 1; j < m; j++) {
			// go to first hole in current line
			if (map[i][j] != HOLE)
				continue;
			
			// if it is a single hole with no neighbours (vertical or horizontal)
			// fill the hole
			if (has_no_line_neighbours(map, i, j, n , m) && !has_vertical_neighbours(map, i, j, n)) {
				map[i][j] = NO;
				NO++;
				map[i][0]--;
				map[0][j]--;
			}
			// coordinates for potential new line block
			if (!saved_coords) {
				start_i = i;
				start_j = j;
				saved_coords = 1;
			}
			
			// look-up first hole that has no vertical neighbour holes (isolated)
			if (has_vertical_neighbours(map, i, j, n))
				continue;
			
			cover_line_of_isolated(map, start_i, start_j, n, m, NO);
			saved_coords = 0;
		}
	}
				
}

int main()
{
	int n, m, **map = NULL;
	
	map = read_map(&n, &m);
	if (NULL == map)
		return EXIT_FAILURE;
	
	print_map(map, n, m);
	printf("\n");
	isolated_on_line(map, n, m);
	print_map(map, n, m);
	
	free_mat(map, n, m);	
	return 0;
}
