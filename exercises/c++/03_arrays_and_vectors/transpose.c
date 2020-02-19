#include <iostream>
#include <utility>
#include <array>
#include <iomanip>

#define NMAX 100

//HEADERS
bool transpose(std::array<double, NMAX>& mat, int& a, int& b);
void printmat(const std::array<double, NMAX> mat, const int a, const int b);


int main()
{
    //test with matrix 3x3
    int a{3}, b{3};
    std::array<double,NMAX> mat3x3{1,2,3,4,5,6,7,8,9};
    
    std::cout << "Matrix 3x3: " << std::endl;
    printmat(mat3x3, a, b);
    transpose(mat3x3, a, b);
    std::cout << "Transposed 3x3: " << std::endl;
    printmat(mat3x3, a, b);

    //test with matrix 3x2
    a=3;
    b=2;
    std::array<double,NMAX> mat3x2{1,2,3,4,5,6};
    std::cout << "Matrix 3x2: " << std::endl;
    printmat(mat3x2, a, b);
    transpose(mat3x2, a, b);
    std::cout << "Transposed 3x2: " << std::endl;
    printmat(mat3x2, a, b);

    //test with matrix 2x3
    a=2;
    b=3;
    std::array<double,NMAX> mat2x3{1,2,3,4,5,6};
    std::cout << "Matrix 2x3: " << std::endl;
    printmat(mat2x3, a, b);
    transpose(mat2x3, a, b);
    std::cout << "Transposed 2x3: " << std::endl;
    printmat(mat2x3, a, b);
}

//function: traspose; invert a matrix passed as an std::array
//INPUT: 
//   +std::array, mat; array which contains the elenents of a matrix of dimension a x b
//   +int, a: number of rows of the matrix
//   +int, b: number of columns of the matrix
//OUTPUT: false if dimension is too much big.
bool transpose(std::array<double, NMAX>& mat, int& a, int& b)
{
    int mypos, swappos;
    std::array<bool, NMAX> used;  //array which control if one element has been used    
    for(bool x : used)
	    x=false;

    if(a*b>NMAX)
        return false;
    
    else
    {
        for(int i{0};i<a;++i){
            for(int j{0};j<b;++j)
	    {
                mypos=i*b+j;
		swappos=j*a+i;
		if(!used[mypos])
		{
		   std::swap(mat[mypos],mat[swappos]);
		   used[swappos]=true;
		}
	    }
        }
        std::swap(a,b); 
        return true;
    }
}

//function: printmat; print a matrix passed as an std::array on stdin
//INPUT: 
//   +const std::array, mat; array which contains the elenents of a matrix of dimension a x b
//   +const int, a: number of rows of the matrix
//   +const int, b: number of columns of the matrix
//OUTPUT: -
void printmat(const std::array<double, NMAX> mat, const int a, const int b)
{
    for(int i{0};i<a;i++){
        for(int j{0};j<b;j++)
            std::cout << std::setw(3) << mat[j+i*b];
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    return;
}
