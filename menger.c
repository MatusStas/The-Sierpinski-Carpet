#include <stdio.h>
#include <stdlib.h>


int size_of_grid(int iteration) {
	int three = 1;
	for(int i = 0; i < iteration; i++)
		three*=3;
	return three;
}


int expo(int n, int e) {
	int result = 1;
	for(int i = 0; i < e; i++)
		result*= n;
	return result;
}


void paint(int x, int y, int *arr[], int size) {
	for(int i = x; i < x + size; i++)
		for(int j = y; j < y + size; j++)
			*(*(arr + i) + j) = 1;
}


void load(int *iteration, int *arr[], int *grid_size) {
	int list[*iteration];
	for(int x = 0; x < *iteration+1; x++)
		list[x] = expo(3,x);

	for(int ite = 0; ite < *iteration; ite++)
		for(int i = 0; i < *grid_size; i++)
			for(int j =0; j < *grid_size; j++)
				if(i%list[ite+1] == list[ite] && j%list[ite+1] == list[ite])
					paint(i,j,arr,list[ite]);
}


void write(int *arr[], int *grid_size) {
	FILE *fw;
	fw = fopen("menger.ppm","w");
	fprintf(fw, "%s\n", "P3");
	fprintf(fw, "%d %d\n", *grid_size,*grid_size);
	fprintf(fw, "%d\n%c\n%c\n%c", 255,'r','g','b');

	for(int i = 0; i < *grid_size; i++)
		for(int j = 0; j < *grid_size; j++)
			if(arr[i][j] == 0)
				fprintf(fw, "\n%d\n%d\n%d", 0,0,0);
			else{fprintf(fw, "\n%d\n%d\n%d", 255,255,255);}

	fclose(fw);
}


int main() {
	int grid_size,
		iteration;

	printf("Number of iterations:\n");
	scanf("%d",&iteration);
	grid_size = size_of_grid(iteration);

	int *arr[grid_size];
	arr[grid_size] = (int *) malloc(grid_size * sizeof(int));
	for(int i = 0; i < grid_size; i++)
		arr[i] = (int *) malloc(grid_size * sizeof(int));

	load(&iteration, arr, &grid_size);
	write(arr,&grid_size);
	return 0;
}