#include <iostream>
#include <cstdlib>
#include <omp.h>
using namespace std;

int main() {
    const long long int size = 10000000;  
    long long int * arr = new long long int[size];
    
    for (long long int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }

    long long int evenCount = 0, oddCount = 0;
    long long int evenSum = 0, oddSum = 0;

    #pragma omp parallel for reduction(+:evenCount, oddCount, evenSum, oddSum)
    for (long long int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) { 
            evenCount++;
            evenSum += arr[i];
        } else {  
            oddCount++;
            oddSum += arr[i];
        }
    }

    cout << "\nParallel Approach: " << endl;
    cout << "Even numbers count: " << evenCount << ", Sum: " << evenSum << endl;
    cout << "Odd numbers count: " << oddCount << ", Sum: " << oddSum << endl;

    return 0;
}

