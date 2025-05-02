#include <iostream>
#include <algorithm>
#include <omp.h>

using namespace std;

void display(int * arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void distributed_histogram_sort_parallel(int * arr, int n, int num_bins) {
    if (n == 0) return; 

    int min_val = 99999, max_val = -9999;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }

    int bin_size = (max_val - min_val + 1) / num_bins;
    if (bin_size == 0) bin_size = 1; 
    
    int bins[num_bins][n];  
    int bin_counts[num_bins] = {0};  

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        int bin_index = (arr[i] - min_val) / bin_size;
        if (bin_index >= num_bins) bin_index = num_bins - 1; 
        
		#pragma omp critical
		{
			bins[bin_index][bin_counts[bin_index]] = arr[i];
        	bin_counts[bin_index]++;
		}
    }

    #pragma omp parallel for
    for (int i = 0; i < num_bins; i++) {
        sort(bins[i], bins[i] + bin_counts[i]); 
    }

    int index = 0;
    for (int i = 0; i < num_bins; i++) {
        for (int j = 0; j < bin_counts[i]; j++) {
            arr[index++] = bins[i][j];
        }
    }
}

int main() {
    
    int n,bins;
    cout<<"Enter the number of elements in the array : ";cin>>n;
    int * A = new int [n];
    
    cout<<"Enter the array elements : ";
    for(int i = 0; i < n ; i++){
    	cin>>A[i];
	}

    cout<<"Enter the number of bins : ";cin>>bins;

    cout << "Original array:" << endl;
    display(A, n);

    distributed_histogram_sort_parallel(A, n, bins);

    cout << "Sorted array after distributed histogram sort:" << endl;
    display(A, n);

    return 0;
}

