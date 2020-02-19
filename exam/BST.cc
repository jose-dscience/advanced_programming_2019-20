/*
 * José Antonio Fernández Santisteban (DSSC student)
 * Nicola Miolato (DSSC student)
 *
 * Advanced Programming Exam
 *
 * In this source file we have made profs over out bst library. 
 * 
 * -Requirements: 
 *     +    g++ (8.3.0)
 *     +    c++14
 *     +    bst.h
 * 
 * -Compilation: g++ BST.cc -o BST.x -std=c++14 -Wall -Wextra
 *          
 */

#include "bst.h"
#include <string>

int main()
{
    using _bst = bst<int,std::string,bool>;
    using _pair = std::pair<int,std::string>;
    
    std::cout << "+>Testing constructors:\n";
    _bst b0{};
    std::cout << "  ->bst b0{}: " << b0 << "\n";
    _bst b1{_pair(1,"uno")};
    std::cout << "  ->bst b1{pair(1,\"uno\")}: " << b1 << "\n";
    _bst b2{[](int const a, int const b) {return a>b;}};
    std::cout << "  ->bst b2{comp(a>b)}: " << b2 << "\n";
    std::cout << std::endl;
    
    std::cout << "+>Testing move semantics:\n";
    b2 = std::move(b1);
    std::cout << "  ->b2 = std::move(b1): " << b2 << "\n";
    std::cout << std::endl;
    
    std::cout << "+>Testing copy semantics:\n";
    _bst b3{};
    b3 = b2;
    b3[1] = "one";
    std::cout << "  ->b3 = b2; b3[1]=\"one\";    b2: " << b2 << "    b3: " << b3 << "\n";
    std::cout << std::endl;
    
    std::cout << "+>Testing insert and emplace:\n";
    _bst b4{_pair(8,"ocho")};
    b4.insert(_pair(3,"tres"));
    b4.emplace(10,"diez");
    b4.insert(_pair(1,"uno"));
    b4.emplace(6,"seis");
    b4.insert(_pair(4,"cuatro"));
    b4.emplace(7,"siete");
    b4.insert(_pair(14,"catorce"));
    b4.emplace(13,"trece");
    std::cout << "  ->constructs example with inserts and emplaces b4: " << b4 << "\n";
    
    std::cout << "+>Testing erase, balance and clear:\n";
    b4.erase(8);
    b4.erase(6);
    b4.erase(100);
    std::cout << "  ->erase 8, 6, 100 b4: " << b4 << "\n";
    b4.erase(10);
    b4.emplace(-1,"menos uno");
    b4.emplace(-3,"menos tres");
    b4.emplace(-4,"menos cuatro");
    std::cout << "  ->before balance():\n";
    b4.strong_print();
    std::cout << "  ->after balance():\n";
    b4.balance();
    b4.strong_print();
    std::cout << std::endl;
    
}
