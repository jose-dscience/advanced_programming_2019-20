#include <iostream>
#include <utility>
#include <memory>


    //template <typename nval_type>
    template <typename nkey_type, typename nval_type>
    struct node
    {
        std::pair<nkey_type, nval_type> content;
        std::unique_ptr<node<nkey_type, nval_type>> right;
        std::unique_ptr<node<nkey_type, nval_type>> left;
        node<nkey_type, nval_type>* head;
        const node<nkey_type, nval_type>* previous;
        
        //custom ctor(content)
        explicit node(const std::pair<nkey_type, nval_type> val) 
        : content{val}
        , right{nullptr}
        , left{nullptr}
        , previous{nullptr}
        , head{nullptr}
        {}
        
        //custom ctor(prev., pather node)
        explicit node(const std::pair<nkey_type, nval_type> val, const node<nkey_type, nval_type>* n0)
        : content{val}
        , right{nullptr}
        , left{nullptr}
        , previous{n0}
        , head{nullptr}
        {}
        
        //custom ctor(prev., pather node, root node)
        explicit node(const std::pair<nkey_type, nval_type> val, const node<nkey_type, nval_type>* n0, node<nkey_type, nval_type>* nr)
        : content{val}
        , right{nullptr}
        , left{nullptr}
        , previous{n0}
        , head{nr}
        {}
        
        //default ctor
        node()
        : content{std::pair<nkey_type, nval_type>{}}
        , right{nullptr}
        , left{nullptr}
        , previous{nullptr}
        , head{nullptr}
        {std::cout << "hola\n";}
        
        //copy ctor
        node(const node& n0)
        : content{n0.content}
        , right{nullptr}
        , left{nullptr}
        , previous{nullptr}
        , head{nullptr}
        {}
        
        //move ctor
        node(node&& n0)
        : content{std::move(n0.content)}
        , right{std::move(n0.right)}
        , left{std::move(n0.left)}
        , previous{std::move(n0.previous)}
        , head{std::move(n0.head)}
        {}
        
        //move assignment
        node& operator=(node&& n0) 
        {
            content = std::move(n0.content);
            right = std::move(n0.right);
            left = std::move(n0.left);
            previous = std::move(n0.previous);
            head = std::move(n0.head);
            
            return (*this);
        }
        
        //copy assignment
        node operator=(const node& n0) 
        {
            node n1 = n0;
            (*this) = std::move(n1);
            return (*this);
        }
        
        // destructor
        ~node()
        {
            left.reset();
            right.reset();
        }
    };
    
int main(void)
{
    node<int, int> n0(std::pair<int, int>(3,3));
    std::cout << (n0.content).first << "\n";
    std::cout << std::endl;
    
    node<int, int> n1(std::pair<int, int>(1,1), &n0);
    std::cout << "n0: " << ((n1.previous)->content).first << "; n1: " << (n1.content).first <<";\n";
    std::cout << std::endl;
    
    node<int, int> n2(std::pair<int, int>(2,2), &n1, &n0);
    std::cout << "Me: " << (n2.content).first << "; prev: " << ((n2.previous)->content).first << "; head: " << ((n2.head)->content).first <<";\n";
    std::cout << std::endl;
    
    node<int, int> n3(std::move(n2));
    std::cout << "Me: " << (n3.content).first << "; prev: " << ((n3.previous)->content).first << "; head: " << ((n3.head)->content).first <<";\n";
    std::cout << std::endl;
    
    node<int, int> n4{};
    n4 = std::move(n3);
    std::cout << "Me: " << (n4.content).first << "; prev: " << ((n4.previous)->content).first << "; head: " << ((n4.head)->content).first <<";\n";
    std::cout << std::endl;
    
    node<int, int> n5{};
    n5 = n4;
    std::cout << "Me: " << (n4.content).first <<";\n";
    std::cout << std::endl;
    
}
