//
//  main.c
//  SortingAlgorithms
//
//  Created by Adam Cotugno on 3/30/14.
//  Copyright (c) 2014 Adam Cotugno. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>

void quickSort( int[], int, int);
int partition( int[], int, int);
void swap (int array[], int index1, int index2);

void mergeSort (int array [], int lowBound, int highBound);
void merge (int array[], int lowBound, int midpoint, int highBound);

void bubbleSort (int array[], int count);

void shellSort (int array[], int count);

void insertionSort (int array[], int count);

void insertionSort (int array[], int count) {
	for (int i = 1; i < count; i++) {
		for (int j = i; j > 0 && array[j] < array[j-1]; j--) {
			swap(array, j, j-1);
		}
	}
}


void shellSort (int array[], int count) {
	int interval = 1;
	
	//Set to the max interval we can use for this array size
	while (interval < count) {
		interval = 3 * interval + 1;
	}
	
	//For each interval in the gap sequence...
	for (NULL; interval > 0; interval = interval/3) {
		printf("\nInterval being evaluated is %d", interval);
		for (int i = interval; i < count; i++){
			//Store the starting item
			printf("\n\nEvaluating items:\n");
			for(int k = i; k >= 0; k -= interval)
				printf(" %d ", array[k]);
			
			int temp = array[i];
			int j;
			//Swap items at the gap interval as needed where the lower element is higher than the higher element
			for (j = i; j >= interval && array[j - interval] > temp; j -= interval) {
				array[j] = array[j - interval];
				printf("\nSwap occurred index %d to %d, array is:\n", (j-interval), j);
				for(int k = 0; k < 9; k++)
					printf(" %d ", array[k]);
			}
			//Put the starting item in its proper location
			array[j] = temp;
			printf("\nFinished evaluating, array is:\n");
			for(int k = 0; k < 9; k++)
				printf(" %d ", array[k]);
		}
	}
}


void bubbleSort (int array[], int count) {
	if (count > 1) {
		bool didSwap = 0;
		//For our count of elements
		for (int i = 0; i < count; i++) {
			//Start from the last element and "bubble" up the smallest values
			for (int j = count - 1; j > i; j--) {
				if (array[j] < array [j-1]) {
					swap(array, j, j-1);
					didSwap = 1;
				}
			}
			
			if (didSwap == 0) {
				break;
			}
		}
	}
}


void quickSort( int array [], int lowBound, int rightBound) {
	if (lowBound < rightBound) {
		int pivot = partition(array, lowBound, rightBound);
		quickSort(array, lowBound, pivot - 1);
		quickSort(array, pivot + 1, rightBound);
	}
}


int partition (int array [], int leftBound, int rightBound) {
	int pivot = array [leftBound]; //Because, why not!
	int leftPointer = leftBound + 1;
	int rightPointer = rightBound;
	
	printf("Pivot selected is %i:\n", pivot);
	printf("Evaluating on:\n");
	for(int logCount = leftBound; logCount <= rightBound; logCount++) {
		printf("%d ", array [logCount]);
	}
	printf("\n\n");

	while (1) {
		//Move pointer right until an element is greater thant he pivot
		//but before we reach the right bound
		while (array [leftPointer] <= pivot && leftPointer <= rightBound) {
			leftPointer ++;
			continue;
		}
		
		//Move pointer left until an element is less thant the pivot
		while (array [rightPointer] > pivot) {
			rightPointer--;
			continue;
		}
		
		//If our right pointer has traveled all the way to the left pointer
		//we've covered every element (and the rightPointer is now at the last element
		//that is less than the pivot)
		if (leftPointer < rightPointer) {
			//Rotate our elements around the pivot
			swap (array, leftPointer, rightPointer);
		} else {
			break;
		}
	}
	
	//Swap the pivot to the midpoint of the sorted array completing the last pivot of this sort
	//(as element at rightPointer is less than or equal to the pivot)
	swap (array, leftBound, rightPointer);
	printf("Midpoint is index %i\n",rightPointer);
	printf("Pivot shifted to midpoint:\n");
	for(int logCount = 0; logCount < 9; logCount++) {
		printf("%d ", array [logCount]);
	}
	printf("\n\n\n");

	return rightPointer;
}


void swap (int array[], int index1, int index2) {
	int tempElement = array [index1];
	array [index1] = array [index2];
	array [index2] = tempElement;
	printf("Single shift excecuted:\n");
	printf("Index %i with index %i\n", index1, index2);
	
	for(int logCount = 0; logCount < 9; logCount++) {
		printf("%d ", array [logCount]);
	}
	printf("\n");
}


int main(int argc, const char * argv[]) {
	// Insert code here...
	int array [] = {7, 42, 0, 27, 16, 8, 4, 15, -15};
	
	int i;
	printf("\n\nUnsorted array is:  ");
	for(i = 0; i < 9; i++)
		printf(" %d ", array[i]);
	
	printf("\n");
	insertionSort(array, 9);
	
	printf("\n\nSorted array is:  ");
	for(i = 0; i < 9; i++)
		printf(" %d ", array[i]);
    return 0;
}


void mergeSort (int array[], int lowBound, int highBound) {
	if (lowBound < highBound) {
		int midpoint = (highBound + lowBound)/2;
		//Recursively run until we have one element comparisons
		mergeSort(array, lowBound, midpoint);
		mergeSort(array, midpoint + 1, highBound);
		
		printf("\n\nMerging\n");
		for(int i = lowBound; i <= midpoint; i++)
			printf(" %d ", array[i]);
		
		printf("\nand\n");
		for(int j = midpoint + 1; j <= highBound; j++)
			printf(" %d ", array[j]);
		merge(array, lowBound, midpoint, highBound);
		printf("\n\nRecursion finished, array is:  ");
		for(int k = 0; k < 9; k++)
			printf(" %d ", array[k]);
	}
}


void merge (int array[], int lowBound, int midpoint, int highBound) {
	int tempArray[100];
	int leftHalfPointer = lowBound, rightHalfPointer = midpoint + 1, tempArrayPointer = 0;
	
	while (leftHalfPointer <= midpoint && rightHalfPointer <= highBound) {
		if (array[leftHalfPointer] < array[rightHalfPointer]) {
			tempArray[tempArrayPointer] = array[leftHalfPointer];
			tempArrayPointer++;
			leftHalfPointer++;
		} else {
			tempArray[tempArrayPointer] = array[rightHalfPointer];
			tempArrayPointer++;
			rightHalfPointer++;
		}
	}
	
	while (leftHalfPointer <= midpoint) {
		tempArray[tempArrayPointer] = array[leftHalfPointer];
		tempArrayPointer++;
		leftHalfPointer++;
	}
	
	while (rightHalfPointer <= highBound) {
		tempArray[tempArrayPointer] = array[rightHalfPointer];
		tempArrayPointer++;
		rightHalfPointer++;
	}
	
	tempArrayPointer--;
	
	//Putting the result back in the original array, in order now
	while (tempArrayPointer >= 0) {
		array [lowBound + tempArrayPointer] = tempArray[tempArrayPointer];
		tempArrayPointer--;
	}
}
