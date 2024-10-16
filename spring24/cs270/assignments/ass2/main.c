// main.c
// Sebastian Nuxoll
// CS 270
#include <stdio.h>

extern int sum(int[], int);
extern double average(int[], int);
extern int min(int[], int);
extern int max(int[], int);

int main() {
	int arr[] = 
	{10, 4, 8, 7,14, 8, 7, 7,11,15, 8,12,11, 6, 6,10,11,13,10,14, 6, 5,11, 5, 8,
	  6, 9, 9,12,12,13,13, 8,10,13, 7,10,10,12,13, 7,10,11,12,13,15,12, 7, 9, 9,
	  7,10,15,11,13, 9, 8, 7, 8,12, 7, 8, 9, 7,16, 4, 5,15,11,12, 6, 9,12,10, 7,
	 12,11,12,10,12, 8,12, 9, 9,14,14, 8,12,11, 8, 9, 9, 8,15, 6, 6,10, 8,12, 4};
	int su = sum(arr, 100);
	double av = average(arr, 100);
	int mi = min(arr, 100);
	int ma = max(arr, 100);

	printf("Sum    : %d\n", su);
	printf("Average: %.2f\n", av);
	printf("Maximum: %d\n", ma);
	printf("Minimum: %d\n", mi);
}
