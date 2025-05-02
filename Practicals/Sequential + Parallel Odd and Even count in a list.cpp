# include <iostream>
#include <cstdlib>
#include <omp.h>
using namespace std;

int main(){
	int arr[10];
	for (int i = 0; i < 10; i++) {
        		arr[i] = rand() % 100;
    	}
    	
    	cout<<"The random array is : ";
    	for (int i = 0; i < 10; i++) {
     	   cout << arr[i] << " ";
    	}
    	
    	int evenCount = 0, oddCount = 0;
   	int evenSum = 0, oddSum = 0;
   	
   	for (int i = 0; i < 10; i++) {
		if (arr[i] % 2 == 0) { 
         		evenCount++;
            		evenSum += arr[i];
        		}else { 
            		oddCount++;
            		oddSum += arr[i];
        		}
    	}
    	cout << "\nSequential Approach: "<<endl;
    	cout << "Even numbers count: " << evenCount << ", Sum: " << evenSum << endl;
    	cout << "Odd numbers count: " << oddCount << ", Sum: " << oddSum << endl;
    	
    	
    	int evenC = 0, oddC = 0;
   	int evenS = 0, oddS = 0;

	#pragma omp parallel for reduction(+:evenC, oddC, evenS, oddS)
	for (int i = 0; i < 10; i++) {
	    if (arr[i] % 2 == 0) { 
	        evenC++;
	        evenS += arr[i];
	    } else { 
	        oddC++;
	        oddS += arr[i];
	    }
	}
	
	cout << "Parallel Approach: "<<endl;
	cout << "Even numbers count: " << evenC << ", Sum: " << evenS << endl;
	cout << "Odd numbers count: " << oddC << ", Sum: " << oddS << endl;


    return 0;
}


