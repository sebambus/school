// min.c
// Sebastian Nuxoll
// CS 270
int min(int arr[], int size) {
	int n = arr[0];
	for(int i = 1; i < size; i++)
		if(arr[i] < n)
			n = arr[i];
	return n;
}
