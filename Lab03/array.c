
#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>  had to comment this header file out looked on stackoverflow and they state it has been deprecated

// We need to pass the size of the array because in C we don't have access to the array length. If we can't determin the size of the array, you will be presented with a seg fault
// The original array is not returned at the end of the functions, we copy the values from the original array in a pointer array called s_arr
// In the main function after our bubbleSort function, the main function wants to still hold on the value of our earlier array and print that out. If we were to just use the same array for bubble sort(which we can), when we try printing our original array it will rather return a sorted array

int* bubbleSort(int arr[], int n){
    int temp, i = 0, j = 0;
    int *s_arr = (int*)malloc(n * sizeof(int));

    // Copy arr to s_arr
    for(i=0; i<n; i++)
        *(s_arr + i)  = arr[i];

    // Actual sorting using array notations
	// Comment this when implementing pointer version.
    //for (i=0;i<n-1;i++){
    //    for(j=0;j<n-1;j++){
    //        if(s_arr[j] > s_arr[j+1]){
    //            temp = s_arr[j+1];
    //            s_arr[j+1] = s_arr[j];
    //            s_arr[j] = temp;
    //        }
    //    }
    // }

    // Actually sorting using pointer notations. i.e. you cannot use "[]"!
    // Your code goes here...
	for(i = 0; i < n-1; i++){
		for(j = 0; j < n-1; j++){
			if(*(s_arr + j) > *(s_arr + (j+1))){
				temp = *(s_arr + (j+1));
				*(s_arr + (j+1)) = *(s_arr + j);
				*(s_arr + j) = temp;
			}
		}
	}


    return s_arr;

}

void printArray(int arr[], int n){
    int i = 0;
    printf("[");
    for(i=0; i<n; i++)
        printf("%d ", arr[i]);
    printf("]\n");
}

int bSearch(int *arr, int a, int b, int key){
    // Binary search function. arr is the array, key is the value to search for, a and b are the boundaries of arr to be searched within.
    // You must use pointer notations. i.e. no "[]"
    // Your code goes here:
	int mid = (b-a)/2;
	if(a == b){
		if(*(arr + a) == key){
			return a;
		}
	}
	int midVal = *(arr+(a+mid));	
	if(key == midVal){
		return a+mid;
	} else if (key < midVal){
		return bSearch(arr, a,a+ mid, key);
	} else if (key > midVal){
		return bSearch(arr, a+mid+1, b, key);
	}

	return -1; // Modify this to return an appropriate value!
	// { 1, 2, 3, 4, 5 }
	// { 1, 2, 3, 4, 5, 6 }
}
 int main() {

    int i = 0, size = 0, key = 0, result = 0;
    int *array, *sorted;

    printf("How big is your array?  ");
    scanf("%d", &size);
    array = (int*)malloc(size * sizeof(int));

    for(i=0; i<size; i++){
        printf("Please enter array[%d]:  ", i);
        scanf("%d", &array[i]);
    }

    printf("Please wait while I sort your numbers...\n");
    sorted = bubbleSort(array, size);
    printf("Here is your original array:\n");
    printArray(array, size);
    printf("Here is your SORTED array: \n");
    printArray(sorted, size);
    printf("What number are you looking for? ");
    scanf("%d", &key);
    printf("OK, let me see if I can find a \"%d\" in the array...\n", key);
    result = bSearch(sorted, 0, size-1, key);
    if(result != -1)
        printf("Got it! A \"%d\" is at index %d.\n", key, result);
    else
        printf("I'm sorry, a \"%d\" cannot be found in the array.\n", key);

	return 0;


}


