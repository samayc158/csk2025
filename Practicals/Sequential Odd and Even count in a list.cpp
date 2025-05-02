#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    const long long int size = 1000000000;
    long long int * arr = new long long int[size];
    long long int evenCount = 0, oddCount = 0;
    long long int evenSum = 0, oddSum = 0;

    for (long long int i = 0; i < size; i++) {
        arr[i] = rand() % 100;  
    }
    
    for(long long int i= 0 ; i < size ; i++){
    	if (arr[i] % 2 == 0) {  
            evenCount++;
            evenSum += arr[i];
        } else {  
            oddCount++;
            oddSum += arr[i];
        }
    }

    cout << "\nSequential Approach: " << endl;
    cout << "Even numbers count: " << evenCount << ", Sum: " << evenSum << endl;
    cout << "Odd numbers count: " << oddCount << ", Sum: " << oddSum << endl;

    return 0;
}

