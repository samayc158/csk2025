#include <iostream>
#include <cstdlib>
#include <omp.h>

using namespace std;

int main(){
    int *  A = new int[1000];
    int *  B = new int[1000];
    int C = 0;  
    int C1 = 0;

    for(int i = 0; i < 1000; i++){
        A[i] = (rand() % 100);  
    }

    for(int i = 0; i < 1000; i++){
        B[i] = (rand() % 100);  
    }

    cout << "C = A.B : ";
    for(int i = 0; i < 1000; i++){
        C += (A[i] * B[i]);  
    }

    cout<<"Sequential approach "<<endl;
    cout << "Dot product: " << C << endl;
    
    #pragma omp parallel for reduction(+:C1)
    for (int i = 0; i < 1000; i++) {
	    C1 += (A[i] * B[i]);
    }
    cout<<"Parallel approach "<<endl;
    cout << "Dot product: " << C << endl;
    
    return 0;
}

