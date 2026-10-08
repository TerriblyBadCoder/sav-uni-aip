#include <iostream>
#include <exception>
#include <limits>
void cleanup();
int** initMatrix(unsigned int m, unsigned int n);
void printMatrix(int** matrix, unsigned int m, unsigned int n);
int** transposeMatrix(int** matrix, unsigned int m, unsigned int n);
int main(int argc, char *argv[])
{
	try(){
		unsigned int m = 0, n = 0;
		std::cout << "Ввод количества строк, столбцов \n";
		std::cin >> n >> m;
		cleanup();
		if(m==0||n==0){
			return 1;
		}
		std::cout << "Ввод матрицы \n";
		int** matrixed =initMatrix(m,n);
		for(unsigned int i = 0; i < n; i++){
			
				int* arrayed = (int*)malloc(m*sizeof(int));
				if(arrayed==nullptr){return 2;}
				for(unsigned int j = 0;j<m;j++){
					int yea = 0;
					std::cin >> yea;
					arrayed[j]=yea;
				}
				cleanup();
				for(unsigned int j = 0;j<m;j++){
				matrixed[i][j]=arrayed[j];
				}
				free(arrayed);
			
		}
		std::cout << "Обычная: \n";
		printMatrix(matrixed,m,n);
		int ** transposed = transposeMatrix(matrixed,m,n);
		std::cout << "\nТранспозированная: \n";
		printMatrix(transposed,n,m);
	}
	catch(const bad_alloc& e){
		return 2;
	}
}
int** initMatrix(unsigned int m, unsigned int n){
	int** matrixed = (int**)malloc(n*sizeof(int*));
	if(matrixed==nullptr){throw std::bad_alloc();}

	for (unsigned int i = 0; i < m; ++i) {
        int* tempCheck = (int*)malloc(m * sizeof(int));
		if(tempCheck==nullptr){throw std::bad_alloc();}
		matrixed[i]=tempCheck;
	}
	return matrixed;
}
int** transposeMatrix(int** matrix, unsigned int m, unsigned int n){
	int maximum = n;
	if(m>n)maximum=m;
	int** transposed = initMatrix(maximum,maximum);
	for(unsigned int j = 0;j<m;j++){
		for(unsigned int i = 0; i < n; i++){
			transposed[j][i]=matrix[i][j];
		}
	}
	return transposed;
}
void printMatrix(int** matrix, unsigned int m, unsigned int n){
	for(unsigned int i = 0; i < n; i++){
		for(unsigned int j = 0;j<m;j++){
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}
void cleanup(){
	if(std::cin.fail()){std::cin.clear(std::cin.rdstate()^std::ios_base::failbit);}
	std::cin.ignore(32,'\n');
}
