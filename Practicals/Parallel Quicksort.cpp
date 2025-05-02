#include <iostream>
#include <omp.h>

using namespace std;

void display(int * A , int n){
	for(int i = 0 ; i < n ; i++){
		cout<<A[i]<<" ";
	}
	cout<<endl;
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        #pragma omp task shared(arr)
        quicksort(arr, low, pi - 1);

        #pragma omp task shared(arr)
        quicksort(arr, pi + 1, high);

        #pragma omp taskwait
    }
}

int main() {
    int n;
    cout<<"Enter the size of the array : ";cin>>n;
    
    int * A = new int [n];
    
    cout<<"Enter the elements of array : ";
    for(int i = 0 ; i < n ; i++){
    	cin>>A[i];
	}

    cout << "Original array:\n";
    display(A,n);

    #pragma omp parallel
    {
        #pragma omp single
        quicksort(A, 0, n - 1);
    }

    cout << "Sorted array:\n";
    display(A,n);

    return 0;
}

