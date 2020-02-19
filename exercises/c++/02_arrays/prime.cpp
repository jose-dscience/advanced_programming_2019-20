#include<iostream>
bool prime_detector(int num, int* primes, int n);


//prime detector: detects if a number it's prime or not.
//IMPUTS:   int num, the number in question
//          int* primes, one array (pointer) that contains all prime numbers found out
//          std::size_t n, the number of elements of the primes list
//OUTPUT:   true (it's prime) or false (it's not)

template <typename T>
bool prime_detector(T num, T* primes, T n)
{
    for(T i{0}; i<n; i++) //loop over all primes
    {
        if(num%primes[i] == 0)  //if it detect any factor of the number, return false inmediatly
            return false;
        else
            continue;
    }
    
    return true;
}

//main function
//COMMENTS
//I decided to asign memory of each prime in each iteration in order to not to overload the heap.
int main(void)
{
    int* primes{new int[1]};
    int n{1};  //primes found-out
    int* primesaux{new int[1]};
    
    *primes=2;
    
    
    for(int i{3}; i<100; i+=2) //I consider only odd numbers as pair numbers cannot be primes (except 2)
    {
        if(prime_detector<int>(i,primes,n)) //If prime is found, assign memory and save it in the list
        {
            primesaux = new int[n];  //new auxiliar array, a resized-version of primes array
            
            for(int j{0};j<n;j++)  //I copy primes array values into the auxiliar resized array
                primesaux[j]=primes[j];
            
            
            primes=new int[n];  //resize primes array
            
            
            delete[] primes; //delete primes array memory and assign to primes the memory of primesaux (I'm renaming)
            primes=primesaux;
            
            primes[n]=i; //add new element to primes array
            
            n++;
        }
        else
            continue;
    }
    
    for(int i{0}; i<n; i++)    //print prime numbers
        std::cout << primes[i] << " ";
    std::cout << std::endl;
    
    delete[] primes; //disallocate primes/primesaux memory
    
    return 0;
}
