#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions
void printPuzzle(char** arr, int n);
void searchPuzzle(char** arr, int n, char** list, int listSize);

// Main function, DO NOT MODIFY (except line 52 if your output is not as expected -- see the comment there)!!!	
int main(int argc, char **argv) {
    int bSize = 15;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    char **block = (char**)malloc(bSize * sizeof(char*));
	char **words = (char**)malloc(50 * sizeof(char*));

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

	// Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block+i) = (char*)malloc(bSize * sizeof(char));

        fscanf(fptr, "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", *(block+i), *(block+i)+1, *(block+i)+2, *(block+i)+3, *(block+i)+4, *(block+i)+5, *(block+i)+6, *(block+i)+7, *(block+i)+8, *(block+i)+9, *(block+i)+10, *(block+i)+11, *(block+i)+12, *(block+i)+13, *(block+i)+14 );
    }
	fclose(fptr);

	// Open file for reading word list
	fptr = fopen("states.txt", "r");
	if (fptr == NULL) {
        printf("Cannot Open Words File!\n");
        return 0;
    }
	
	// Save words into arrays
	for(i = 0; i < 50; i++) {
		*(words+i) = (char*)malloc(20 * sizeof(char));
		fgets(*(words+i), 20, fptr);		
	}
	
	// Remove newline characters from each word (except for the last word)
	for(i = 0; i < 49; i++) {
		*(*(words+i) + strlen(*(words+i))-2) = '\0'; // Change -2 to -1 if line 58 outputs words with the last character missing
	}
	
	// Print out word list
	printf("Printing list of words:\n");
	for(i = 0; i < 50; i++) {
		printf("%s\n", *(words + i));
	}
	printf("\n");
	
	// Print out original puzzle grid
    printf("Printing puzzle before search:\n");
    printPuzzle(block, bSize);
	printf("\n");

	// Call searchPuzzle to find all words in the puzzle
	searchPuzzle(block, bSize, words, 50);
	printf("\n");
	
	// Print out final puzzle grid with found words in lower case
    printf("Printing puzzle after search:\n");
    printPuzzle(block, bSize);
	printf("\n");
	
    return 0;
}

void printPuzzle(char** arr, int n) {
	// This function will print out the complete puzzle grid (arr). It must produce the output in the SAME format as the samples in the instructions.
	// Your implementation here
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%c ", *(*(arr+i)+j));
        }
        printf("\n");
    }


}

void printPos(char** possibilities, int possibilitiesSize){
                for(int k = 0; k < possibilitiesSize; k++){
                    printf("%s, ", *(possibilities+k));
                }
                printf("\n");

}

char* upcase(char* str){
    char* p;
    char* result;
    result = (char*) malloc(strlen(str)*sizeof(char));
    
    strcpy(result, str);
    for(p = result; *p != '\0'; p++){
        if(*p >= 'a' && *p <= 'z'){
            *p += 'A' - 'a';
        }
    }
    return result;
}
char upcaseChar(char chr){
    int ascii = chr;
    char nchr;
    if(ascii >= 97){
        nchr = (char)(ascii-32);
    }else {
        nchr = chr;
    }
    return nchr;
}
char lowcase(char chr){
    int ascii = chr;
    char nchr;
    if(ascii < 97){
        nchr = (char)(ascii+32);
    }else {
        nchr = chr;
    }
    return nchr;
}

void searchingHorizontal(char** arr, int n, char** list, int listSize, char** wordsFound, int* wordsFoundSize){
    for(int i = 0; i < n; i++){ //Iterating through the rows
        for(int j = 0; j < n; j++){ //Iterating thorugh the columns
            char **possibilities = (char**)malloc(50 * sizeof(char*));
            int possibilitiesSize = 0;
            for(int k = 0; k < listSize; k++){
                if((upcaseChar(*(*(arr+i)+j))) == *(*(list+k)+0)){
                    *(possibilities + possibilitiesSize) = (char*)malloc(20 * sizeof(char));


                    strcpy(*(possibilities+possibilitiesSize), *(list+k));
                    possibilitiesSize++;

                }
            }
            
            int it = 1;
            while(possibilitiesSize > 0){
                if(upcaseChar(arr[i][j+it]) == upcaseChar(possibilities[0][it])){
                    if(possibilities[0][it+1] == '\0'){
                        for(int nit = it; nit >= 0; nit--){
                            arr[i][j+nit] = lowcase(arr[i][j+nit]);
                        }
    
                        *(wordsFound + *wordsFoundSize) = (char*)malloc(20 * sizeof(char));
                        *(wordsFound + *wordsFoundSize) = possibilities[0];
                        *wordsFoundSize = *wordsFoundSize + 1;
                        
                    }
                    it++;
                } else{
                    it = 1;
                    possibilities[0] = possibilities[possibilitiesSize-1];
                    possibilitiesSize--;
                }
            }
        
        }
    }
}

void searchingVerticalDOWN(char** arr, int n, char** list, int listSize, char** wordsFound, int* wordsFoundSize){
    for(int i = 0; i < n; i++){ //Iterating through the rows
        for(int j = 0; j < n; j++){ //Iterating thorugh the columns
            char **possibilities = (char**)malloc(50 * sizeof(char*));
            int possibilitiesSize = 0;
            for(int k = 0; k < listSize; k++){
                if((upcaseChar(*(*(arr+j)+i))) == *(*(list+k)+0)){
                    *(possibilities + possibilitiesSize) = (char*)malloc(20 * sizeof(char));
                    strcpy(*(possibilities+possibilitiesSize), *(list+k));
                    possibilitiesSize++;
                }
            }
           
            int it = 1;
            while(possibilitiesSize > 0 && j+it < n){
                if(upcaseChar(arr[j+it][i]) == upcaseChar(possibilities[0][it])){
                    if(possibilities[0][it+1] == '\0'){
                        for(int nit = it; nit >= 0; nit--){
                            arr[j+nit][i] = lowcase(arr[j+nit][i]);
                        }
                        *(wordsFound + *wordsFoundSize) = (char*)malloc(20 * sizeof(char));
                        *(wordsFound + *wordsFoundSize) = possibilities[0];
                        *wordsFoundSize = *wordsFoundSize + 1;
                    }
                    it++;
                } else{
                    it = 1;
                    possibilities[0] = possibilities[possibilitiesSize-1];
                    possibilitiesSize--;
                }
            }
        }
    }
}

void searchingVerticalUP(char** arr, int n, char** list, int listSize, char** wordsFound, int* wordsFoundSize){
    for(int i = 0; i < n; i++){
        for(int j = n-1; j >= 0; j--){
            char **possibilities = (char**)malloc(50 * sizeof(char*));
            int possibilitiesSize = 0;
            for(int k = 0; k < listSize; k++){
                if(upcaseChar((*(*(arr+j)+i))) == *(*(list+k)+0)){
                    *(possibilities + possibilitiesSize) = (char*)malloc(20 * sizeof(char));
                    strcpy(*(possibilities+possibilitiesSize), *(list+k));
                    possibilitiesSize++;
                }
            }
           
            int it = 1;
            while(possibilitiesSize > 0 && j-it > 0){
                if(upcaseChar(arr[j-it][i]) == upcaseChar(possibilities[0][it])){
                    if(possibilities[0][it+1] == '\0'){
                        for(int nit = it; nit >= 0; nit--){
                            arr[j-nit][i] = lowcase(arr[j-nit][i]);
                        }
                        *(wordsFound + *wordsFoundSize) = (char*)malloc(20 * sizeof(char));
                        *(wordsFound + *wordsFoundSize) = possibilities[0];
                        *wordsFoundSize = *wordsFoundSize + 1;
                    }
                    it++;
                } else{
                    it = 1;
                    possibilities[0] = possibilities[possibilitiesSize-1];
                    possibilitiesSize--;
                }
            }
        }
    }
}

void searchingDiagonalDOWN(char** arr, int n, char** list, int listSize, char** wordsFound, int* wordsFoundSize){
    int i = n-1; //9
    int j = 0;
    while(i >= 0){
        for(int j = 0; j <= (n-i-1); j++){
            char **possibilities = (char**)malloc(50 * sizeof(char*));
            int possibilitiesSize = 0;
            for(int k = 0; k < listSize; k++){
                if(upcaseChar((*(*(arr+(i+j))+j))) == *(*(list+k)+0)){
                    *(possibilities + possibilitiesSize) = (char*)malloc(20 * sizeof(char));
                    strcpy(*(possibilities+possibilitiesSize), *(list+k));
                    possibilitiesSize++;
                }
            }

            int it = 1;
            while(possibilitiesSize > 0 && i + j+ it < n){
                if(upcaseChar(arr[i+j+it][j+it]) == upcaseChar(possibilities[0][it])){
                    if(possibilities[0][it+1] == '\0'){
                        for(int nit = it; nit >= 0; nit--){
                            arr[i+j+nit][j+nit] = lowcase(arr[i+j+nit][j+nit]);
                        }
                        *(wordsFound + *wordsFoundSize) = (char*)malloc(20 * sizeof(char));
                        *(wordsFound + *wordsFoundSize) = possibilities[0];
                        *wordsFoundSize = *wordsFoundSize + 1;
                    }
                    it++;
                } else{
                    it = 1;
                    possibilities[0] = possibilities[possibilitiesSize-1];
                    possibilitiesSize--;
                }
            }
        }
        i--;
    }
    i = n-1; //9
    j = 0;
    while(i >= 0){
       for(int j = 0; j+1 <= i; j++){
           char **possibilities = (char**)malloc(50 * sizeof(char*));
           int possibilitiesSize = 0;
           for(int k = 0; k < listSize; k++){
               if(upcaseChar((*(*(arr+j)+(j+(n-i))))) == *(*(list+k)+0)){
                   *(possibilities + possibilitiesSize) = (char*)malloc(20 * sizeof(char));
                   strcpy(*(possibilities+possibilitiesSize), *(list+k));
                   possibilitiesSize++;
               }
           }
           int it = 1;
           while(possibilitiesSize > 0){
               if(upcaseChar(arr[j+it][j+(n-i)+it]) == upcaseChar(possibilities[0][it])){
                   if(possibilities[0][it+1] == '\0'){
                       for(int nit = it; nit >= 0; nit--){
                           arr[j+nit][j+(n-i)+nit] = lowcase(arr[j+nit][j+(n-i)+nit]);
                       }
                       *(wordsFound + *wordsFoundSize) = (char*)malloc(20 * sizeof(char));
                       *(wordsFound + *wordsFoundSize) = possibilities[0];
                       *wordsFoundSize = *wordsFoundSize + 1;
                   }
                   it++;
               } else{
                   it = 1;
                   possibilities[0] = possibilities[possibilitiesSize-1];
                   possibilitiesSize--;
               }
           }
       }
        i--;
    }
    
}

void searchingDiagonalUP(char** arr, int n, char** list, int listSize, char** wordsFound, int* wordsFoundSize){
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= i; j++){
            char **possibilities = (char**)malloc(50 * sizeof(char*));
            int possibilitiesSize = 0;
            for(int k = 0; k < listSize; k++){
                if(upcaseChar((*(*(arr+(i-j))+j))) == *(*(list+k)+0)){
                    *(possibilities + possibilitiesSize) = (char*)malloc(20 * sizeof(char));
                    strcpy(*(possibilities+possibilitiesSize), *(list+k));
                    possibilitiesSize++;
                }
            }
            int it = 1;
            while(possibilitiesSize > 0 && j+it < n && (i-j)-it >= 0){
                if(upcaseChar(arr[i-j-it][j+it]) == upcaseChar(possibilities[0][it])){
                    if(possibilities[0][it+1] == '\0'){
                        for(int nit = it; nit >= 0; nit--){
                            arr[i-j-nit][j+nit] = lowcase(arr[i-j-nit][j+nit]);
                        }
                        *(wordsFound + *wordsFoundSize) = (char*)malloc(20 * sizeof(char));
                        *(wordsFound + *wordsFoundSize) = possibilities[0];
                        *wordsFoundSize = *wordsFoundSize + 1;
                    }
                    it++;
                } else{
                    it = 1;
                    possibilities[0] = possibilities[possibilitiesSize-1];
                    possibilitiesSize--;
                }
            }
        }
    }
    
    for(int i = 1; i < n; i++){
        for(int j = i; j < n; j++){
            char **possibilities = (char**)malloc(50 * sizeof(char*));
            int possibilitiesSize = 0;
            for(int k = 0; k < listSize; k++){
                if(upcaseChar((*(*(arr+(n-j+i-1))+j))) == *(*(list+k)+0)){
                    *(possibilities + possibilitiesSize) = (char*)malloc(20 * sizeof(char));
                    strcpy(*(possibilities+possibilitiesSize), *(list+k));
                    possibilitiesSize++;
                }
            }
            int it = 1;
            while(possibilitiesSize > 0){
                if(upcaseChar(arr[n-j+i-1-it][j+it]) == upcaseChar(possibilities[0][it])){
                    if(possibilities[0][it+1] == '\0'){
                        for(int nit = it; nit >= 0; nit--){
                            arr[n-j+i-1-nit][j+nit] = lowcase(arr[n-j+i-1-nit][j+nit]);
                        }
                        *(wordsFound + *wordsFoundSize) = (char*)malloc(20 * sizeof(char));
                        *(wordsFound + *wordsFoundSize) = possibilities[0];
                        *wordsFoundSize = *wordsFoundSize + 1;
                    }
                    it++;
                } else{
                    it = 1;
                    possibilities[0] = possibilities[possibilitiesSize-1];
                    possibilitiesSize--;
                }
            }
        }
    }
}

void sortWordsFound(char** wordsFound, int* listSize, int letter){
    for(int i = 1; i < *listSize; i++){
        int key = (int)wordsFound[i][letter];
        char* keyword = wordsFound[i];
        int j = i - 1;
        while(j >= 0 && wordsFound[j][letter] > key){
            wordsFound[j+1] = wordsFound[j];
            wordsFound[j] = keyword;
            j--;
        }
       
    }
}



void searchPuzzle(char** arr, int n, char** list, int listSize) {
	// This function checks if arr contains words from list. If a word appears in arr, it will print out that word and then convert that word entry in arr into lower case.
	// Your implementation here
    char** wordsFound = (char**)malloc(listSize * sizeof(char*));
    int wordsFoundSize = 0;
    searchingHorizontal(arr, n, list, listSize, wordsFound, &wordsFoundSize);
    searchingVerticalDOWN(arr, n, list, listSize, wordsFound, &wordsFoundSize);
    searchingDiagonalDOWN(arr, n, list, listSize, wordsFound, &wordsFoundSize);
    searchingDiagonalUP(arr, n, list, listSize, wordsFound, &wordsFoundSize);
    searchingVerticalUP(arr, n, list, listSize, wordsFound, &wordsFoundSize);
    
    int letter = 0;
    sortWordsFound(wordsFound, &wordsFoundSize, letter);
    
    for(int i = 0; i < wordsFoundSize; i++){
        printf("Word found %s\n", *(wordsFound + i));
    }

}

