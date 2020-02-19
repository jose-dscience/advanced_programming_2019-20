#include <iostream>
#include <string>

int main(void){
    double num;
    std::string unit;
    
    std::cin >> num;
    std::cin >> unit;
    
    if(unit == "inch"){
        num=num*25.4e-3;
    }
    else if(unit == "line"){
        num=(num*25.4e-3)/12.;
    }
    else if(unit == "foot"){
        num=num*0.3048;
    }
    else if(unit == "thou"){
        num=(num*25.4e-3)/1000.;
    }
    else if(unit == "yard"){
        num=num*0.91;
    }
    else if(unit == "mile"){
        num=num*1.610;
    }
    else if(unit == "land"){
        num=num*4.8;
    }
    
    std::cout << num << " " << "m" << std::endl;
    
    return 0;
}
