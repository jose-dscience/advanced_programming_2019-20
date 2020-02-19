#include <iostream>

template <typename T>
T* heapassign(std::size_t n);
template <typename T>
void invert(T* ar, std::size_t n);

//This template create a dynamicar allay and ask its content to user
template <typename T>
T* heapassign(std::size_t n)           
{
    T* ar{new T[n]};  //assign array memory
    
    for(std::size_t i{0};i<n;i++)  //fill elements by interaction with user
    {
        std::cout << "  +Introduce element nº " << i << ": "; 
        std::cin >> ar[i];
    }
    
    return ar;  //return the array as a pointer
}

//This template prints an array (passed as a pointer) in inverse order.
template <typename T>
void invertprint(T* ar, std::size_t n)
{
    std::cout << "-----------------------------------------" << std::endl;
    
    for(std::size_t i{n-1}; i>0; i--)
    {
        std::cout << ar[i] << " ";
    }
    std::cout << ar[0] << " ";
    std::cout << std::endl;
    
    return;
}

int main(void)
{
    std::size_t n;
    int* ar;
    
    std::cout << "Introduce array length: ";
    std::cin >> n;
    
    ar=heapassign<int>(n);            //Assignation of memory of ar and fill its content
    
    invertprint(ar, n);      //Plot the inverse array
    
    delete[] ar;     //liberation of memory
    
    return 0;
}
