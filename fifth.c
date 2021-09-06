#include<stdio.h>
#include<stdlib.h>

int** read_m(FILE*, int*);
void free_m(int**, int);
int det_m(int**, int);

int main(int argc, char* argv[argc+1]){
	FILE* fp = fopen(argv[1], "r");
	int s;
	int** mat1 = read_m(fp, &s);
	int det = 0;

	det = det_m(mat1, s);

	printf("%d\n", det);

	free_m(mat1, s);

	fclose(fp);

}

int det_m(int** mat, int s){
	int sum = 0;
	int neg = 1;
	if(s == 1){
		return mat[0][0];
	}
	else if(s == 2){
		return (mat[0][0]*mat[1][1])-(mat[0][1]*mat[1][0]);
	}
	else{
		for(int a=0; a<s; a++){
			int** temp = malloc((s-1)*sizeof(int*));
			for(int i=0; i<s-1; i++){
				temp[i] = malloc((s-1)*sizeof(int));
			}

			for(int i=1; i<s; i++){
				int b = 0;
				for(int j=0; j<s; j++){
					if(j!=a){
						temp[i-1][b] = mat[i][j];
						b++;
					}
				}
			}
			sum = sum+(neg*(mat[0][a]*det_m(temp, s-1)));
			neg = neg*-1;
			free_m(temp, s-1);
		}
	}
	return sum;
}

int** read_m (FILE* fptr, int* m){
	int n;
	fscanf(fptr, "%d\n", &n);

	*m = n;

	/* allocating space for matrix */
	int **mat = malloc(n*sizeof(int*));
	for(int i=0; i<n; i++){
		mat[i] = malloc(n*sizeof(int));
	}

	/* read elements into matrix */
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			fscanf(fptr, "%d", &mat[i][j]);
		}
		fscanf(fptr, "\n");
	}
	return mat;
}

void free_m(int** mat, int m){
	for(int i=0; i<m; i++){
		free(mat[i]);
	}
	free(mat);
}

// gcc -Wall -Werror -fsanitize=address -o test fifth.c