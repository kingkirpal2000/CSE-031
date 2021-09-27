#include <stdio.h>

void printPunishment(repetitionNum, errorNum){
	int i;
	for(i = 1; i <= repetitionNum; i++){
		if(i != errorNum){
			printf("C programming language is the best! ");
		} else {
			printf("C programmming lnguage is the bet! ");
		}
	}
	printf("\n");
}

int main(){
	int repetitionNum, errorNum;
	printf("Enter the number of repetitions phrase:  ");
	scanf("%d", &repetitionNum);
	if(repetitionNum <= 0){
		printf("You entered an invalid value for the number of repetitions! \n");
		return 0;
	} else {
		printf("Enter the repetition count when you wish to introduce a typo:  ");
		scanf("%d", &errorNum);
		if(errorNum <= 0){
			printf("You entered and invalid value for the typo placement! \n");
			return 0;
		} else {
			printPunishment(repetitionNum, errorNum);
			return 1;
		}
	}
	return 0;
}

