#include <iostream>
#include <exception>
#include <limits>
#include <iostream>
#include <exception>
#include <limits>
void cleanup();
int** inputMatrix(size_t *n, size_t *m);
int** initMatrix(size_t n, size_t m);
int** concat_rows(const int * const * lhs, size_t n1, size_t m1, const int * const * rhs, size_t n2, size_t m2);
int main(int argc, char *argv[]){
    try{
        size_t n1=0,m1=0,n2=0,m2=0;
        int** a = inputMatrix(&n1,&m1);
        int** b = inputMatrix(&n2,&m2);

        int** c = concat_rows(a,n1,m1,b,n2,m2);
        std::cout << "\n"; 

    }
    catch(const std::invalid_argument& e){std::cerr<<e.what(); return 1;}
    catch(const std::bad_alloc& e){std::cerr<<e.what(); return 2;}
    catch(...){return 3;}

    return 0;
}
int** initMatrix(size_t n, size_t m){
	int** matrixed = static_cast<int**>(malloc(n*sizeof(int*)));
	if(matrixed==nullptr){throw std::bad_alloc();}

	for (unsigned int i = 0; i < n; ++i) {
        matrixed[i] = static_cast<int*>(malloc(m * sizeof(int)));
		if(matrixed[i]==nullptr){throw std::bad_alloc();}
	}
	return matrixed;
}
int** inputMatrix(size_t* n,size_t* m){
	std::cout << "Ввод размера \n";
    std::cin >> *n >> *m;
    cleanup();
	if(*m==0||*n==0){
	    throw std::invalid_argument("Bad input");
	}
	std::cout << "Ввод матрицы \n";
	int** matrixed =initMatrix(*n,*m);
	for(unsigned int i = 0; i < *n; i++){			
		int* arrayed = (int*)malloc((*m)*sizeof(int));
		if(arrayed==nullptr){throw std::bad_alloc();}
		for(unsigned int j = 0;j<*m;j++){
			int yea = 0;
			std::cin >> yea;
			arrayed[j]=yea;
		}
		cleanup();
		for(unsigned int j = 0;j<*m;j++){
		    matrixed[i][j]=arrayed[j];
		}
		free(arrayed);
	}
    return matrixed;
}

void cleanup(){
	if(std::cin.fail()){std::cin.clear(std::cin.rdstate()^std::ios_base::failbit);}
	std::cin.ignore(32,'\n');
}
int** concat_rows(const int * const * lhs, size_t n1, size_t m1, const int * const * rhs, size_t n2, size_t m2){

    if(lhs==nullptr||rhs==nullptr){throw std::invalid_argument("Bad array");}
    
    size_t n = n1;
    size_t other = n2;
    size_t otherLength = m1;
    if(n<n2){
        n=n2;
        other=n1;    
        otherLength = m2;
    }
    if(m1>std::numeric_limits<size_t>::max()-m2||(n)>std::numeric_limits<size_t>::max()/(m1+m2)){
        //А что иначе?        
        throw std::bad_alloc();
    }
    size_t m = m1+m2;
    int** c = static_cast<int**>(malloc(n*sizeof(int*)));
    if(c==nullptr){throw std::bad_alloc();}
    //Special alloc
    for(size_t i = 0; i < n; i++){
        if(i>=other){
            c[i] = static_cast<int*>(malloc(otherLength*sizeof(int)));
        }else{
            c[i] = static_cast<int*>(malloc(m*sizeof(int)));        
        }
        if(c[i]==nullptr){throw std::bad_alloc();}
    }
    for(size_t i = 0; i < n; i++){
        if(i>=other){
            if(otherLength==m1){
                for(size_t j = 0; j < otherLength; j++){
                    c[i][j]=lhs[i][j];
                }
            }else{
                for(size_t j = 0; j < otherLength; j++){
                    c[i][j]=rhs[i][j];
                }
            }
            continue;        
        }
        for(size_t j = 0; j < m1; j++){
            c[i][j]=lhs[i][j];
        }
        for(size_t j = 0; j < m2; j++){
            c[i][j+m1]=rhs[i][j];
        }
    }
    return c;    
}
