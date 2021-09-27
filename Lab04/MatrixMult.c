
#include <stdio.h>
#include <stdlib.h>

int** matMult(int **a, int **b, int size){
	// (4) Implement your matrix multiplication here. You will need to create a new matrix to store the product.
	
	int** answer = (int**)malloc(size * sizeof(int*));
	for(int i = 0; i < size; i++){
		*(answer + i) = (int*)malloc(size * sizeof(int));
		for(int j = 0; j < size; j++){
			*(*(answer+i)+j) = 0; 
		}
	}


	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			for(int k = 0; k < size; k++){
				*(*(answer+i)+j) += (*(*(a+i)+j) * *(*(b+k)+j));
			}
		}
	}

	return answer;
}

void printArray(int **arr, int n){
	// (2) Implement your printArray function here
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%d ", *(*(arr + i) + j));
		}
		printf("\n");
	}
}

int main() {
	int n = 5;
	int **matA, **matB, **matC;
	// (1) Define 2 (n x n) arrays (matrices). 
	matA = (int**)malloc(n * sizeof(int*));
	matB = (int**)malloc(n * sizeof(int*));
	
	for(int i = 0; i < n; i++){
		*(matA + i) = (int*)malloc(n * sizeof(int));
		*(matB + i) = (int*)malloc(n * sizeof(int));
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			*(*(matA + i) + j) = 0;
			*(*(matB + i) + j) = 0; 
		}
	}
	// This was for testing purposes only 
//	for(int i = 0; i < n; i++){
//		for(int j = 0; j < n; j++){
//			*(*(matA + i) + j) = i+3;
//			*(*(matB + j) + i) = j+i;
//		}
//	}

	// (3) Call printArray to print out the 2 arrays here.
	printf("matA = \n");
	printArray(matA, n);
	printf("matB = \n");
	printArray(matB, n);
	// (5) Call matMult to multiply the 2 arrays here.
	matC = matMult(matA, matB, n);
		
	// (6) Call printArray to print out resulting array here.
	printf("Resulting array = \n");
	printArray(matC, n);

    return 0;
}
