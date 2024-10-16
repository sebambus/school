// sum.c
// Sebastian Nuxoll
// CS 270
int sum(int arr[], int size) {
	int n = 0;
	for(int i = 0; i < size; i++)
		n += arr[i];
	return n;	
}

double average(int arr[], int size) {
	return (double) sum(arr, size) / size;
}
