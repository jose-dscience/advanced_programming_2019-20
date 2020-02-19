#include <iostream>
#include <string>

int main(void)
{
    std::string text1, text2="";
    int i=0;
    
    while(getline(std::cin,text1)){
        if(text2 == text1){
            i++;
            std::cout << i+1 << " " << text1 << std::endl;
        }
        else{
            i=0;
            std::cout << i+1 << " " << text1 << std::endl;
        }
        text2=text1;
    }
    
    return 0;
}
