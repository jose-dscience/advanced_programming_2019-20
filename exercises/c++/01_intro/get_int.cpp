#include <iostream>

int main(void){
    int i;
    
    while(!(std::cin >> i)){
        std::cin.clear();
        std::cin.ignore();
    }
    
    std::cout << "Su int es: " << i << std::endl;
    
    return 0;
}
