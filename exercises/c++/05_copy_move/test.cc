#include <iostream>
#include <memory>

    // private struct node with the proper value_type
    template <class value_type>
    struct node {
        value_type value;
        std::unique_ptr<node> next;
        
        //custom ctor (node)
        explicit node(const value_type val) 
        : value{val}
        , next{nullptr} 
        {}
        
        //default ctor (node)
        node() 
        : value{} 
        , next{nullptr} 
        {}
        
        //copy ctor (node)
        node(const node& n0) 
        : value{n0.value}
        , next{std::move(n0.next.get())}
        {}
        
        //move ctor (node)
        node(node&& n0) 
        :   value{std::move(n0.value)}
        ,   next{std::move(n0.next)}
        {}
        
        //move assignment (node)
        node& operator=(node&& n0) 
        {
            value = std::move(n0.value);             
            next = std::move(n0.next);  
            return *this;
        }
        
        //copy assignment (node)
        node<value_type> operator=(const node& n0)
        {
            auto tmp = n0; 
            (*this) = std::move(tmp);
            
            return *this;
        }
        
        // destructor
        ~node()
        {
            next.reset();
        }
    };

int main(void)
{
    node<int> n0;
    node<int> n1{1};
    //n1.next.reset(new node<int>{n0});
    
    
    node<int> n2{n1};
    
    node<int> n3;
    
    n3 = n2;
    std::cout << "\n\n";
    
    std::cout << n1.value << "\n";
    std::cout << n2.value << "\n";
    std::cout << n3.value << "\n";

    

    
    //HORA: 12:30
    
    
    //auto n3 = n2;
    
    //std::cout << n2->value << "\n";
    //std::cout << n2->next->value << "\n";
    /*
    auto n3 = std::make_unique(node<int>(3, n2));
    std::cout << n3.value << " " << &n3 << "->" << &n3.next << "\n";
    */
}
