#include <stdio.h>

int calculateAverage(avgSum, avgCounter){
	return avgSum / avgCounter;
}

int main(){
	int scannedNum, posAvgSum = 0, negAvgSum = 0, posNumCounter = 0, negNumCounter = 0;
	while(scannedNum != 0){
		printf("Please enter an integer: ");
		if(scanf("%d%*c", &scannedNum)==0) break; // breaks on character input taken from stackover flow "https://stackoverflow.com/questions/25945791/character-input-in-scanfd-value/25946096"
		if(scannedNum > 0){
			posAvgSum += scannedNum;
			posNumCounter++;
		} else if (scannedNum < 0){
			negAvgSum += scannedNum;
			negNumCounter++;
		} else {
			break;
		}
	}
	if(posAvgSum == 0 && negAvgSum == 0) {
		printf("No averages to compute.\n");
	} else {
		if(posAvgSum != 0){
			int pAvg = calculateAverage(posAvgSum, posNumCounter);
			printf("Positive Average: %d\n", pAvg);
		} 
		if (negNumCounter != 0) {
			int nAvg = calculateAverage(negAvgSum, negNumCounter);
			printf("Negative Average: %d\n", nAvg);
		}
	}
	return 0;
}
