#include <iostream>

int main(void){
    float i;
    
    while(!(std::cin >> i)){
        std::cin.clear();
        std::cin.ignore();
    }
    
    std::cout << "Su float es: " << i << std::endl;
    
    return 0;
}
