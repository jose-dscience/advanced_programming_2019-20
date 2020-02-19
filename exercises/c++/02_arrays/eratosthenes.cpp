#include <iostream>

//main function. User must provide a value of n.
//  ->n: maximun number to consider as prime (integer)
int main(void)
{
    size_t n;
    
    std::cout << "Insert a number: ";
    std::cin >> n;
    
    n=n-2; //the first prime number is 2, so I need to exclude 1. I do this by renaming n.
    
    bool* numbers{new bool[n]}; 
    /*Numbers are codified by a boolean array in which each number corrispond to one index of the array and the marked status
     * with its bool value.
     */
    
    for(size_t i{0}; i<n; i++)
        numbers[i] = true;     //true=prime. Initialize array to true.
    
    size_t i{0};
    while(i <= n/2)   //loop over all numbers
    {
        for(size_t j{i+(i+2)}; j<n; j+=(i+2)) //fixed a prime i number, loop over the rest of greater numbers
        {
            
            if(numbers[j])         //if j isn't marked yet, I just mark it.
                numbers[j]=false;
            else
                continue;
        }
        
        do{                 //search the next prime number
            i++;
        }while(!numbers[i]);
    }
    
    for(i=0; i<n; i++)     //print
    {
        if(numbers[i])
            std::cout << i+2 << std::endl;
        else
            continue;
    }
    
    delete[] numbers;
    
    return 0;
}
