# include <iostream>
# include <cstdlib>

using namespace std;

void display(double ** A,int r,int c){
	for(int i = 0 ; i < r ; i++){
		for(int j = 0; j < c ; j++){
			cout<<A[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}
	
int main(){
	
	int rows,mid,cols;
	cout<<"Enter the row and column of matrix 1 : ";cin>>rows>>mid;
	cout<<"Enter the column of matrix 2 : ";cin>>cols;
	
	double ** A = new double * [rows];
	double ** B = new double * [mid];
	double ** C = new double * [rows];
	
	for(int i=0 ; i < rows ; i++){
		A[i] = new double [mid];
		C[i] = new double [cols];
		for(int j = 0 ; j < mid ; j++){
			A[i][j] = (rand() % 100);
		}
		for(int j = 0 ; j < cols ; j++){
			C[i][j] = 0;
		}
	}
	
	for(int i=0 ; i < mid ; i++){
		B[i] = new double [cols];
		for(int j = 0 ; j < cols ; j++){
			B[i][j] = (rand() % 100);
		}
	}
	
	for(int i = 0 ; i < rows ; i++){
		for(int j = 0 ; j < cols ; j++){
			for(int k = 0 ; k < mid ; k++){
				C[i][j] += A[i][k] * B [k][j];
			}
		} 
	}
	

	
	
	return 0;
}
