#include<iostream>
#include<memory>
#include<algorithm>
#include<string>

enum class Insertion_method { push_back, push_front };

template <class value_type_link>
class List {
 public:
  // insert a new node with the value v according to the method m
  // this method should be used to fill the list
  //void insert(const value_type& v, const Insertion_method m);

    // return the size of the list
    std::size_t mysize() const  
    {
        return size;
    }

  // delete all the nodes of the list
  void reset();

  // constructor(s) for List
    //custom constructor
     explicit List(const value_type_link val) 
    : head{std::move(new node<value_type_link>)}
    , size{1}
    {
        head->value=val;
        std::cout <<  "custom ctr" << "\n";
    }
    
    //default constructor
    List()
    : head{nullptr}
    , size{0}
    {std::cout <<  "default ctr" << "\n";}
    
    //copy constructor
    List(const List& l0)
    : size{l0.size}
    , head{nullptr}
    {
        std::cout << "copy ctr" << "\n";
        
        if(size>0)
        {
            head = std::unique_ptr<node<value_type_link>>(new node<value_type_link>);
            node<value_type_link>* n0 = (l0.head).get();
            node<value_type_link>* myn0 = (head).get();
            myn0->value = n0->value;
            
            for(int i=1; i<size; i++)
            {
                myn0->next = std::unique_ptr<node<value_type_link>>(new node<value_type_link>);
                n0 = (n0->next).get();
                myn0 = (myn0->next).get();
                myn0->value = n0->value;
            }
        }
        else
            head.reset();
    }
    
    //move assignement
    List<value_type_link>& operator=(List<value_type_link>&& l0)
    {
        std::cout << "move assignment\n";
        head.reset();
        size = std::move(l0.size);
        head = std::move(l0.head);
        return *this;
    }
    
    //copy assignement
    List<value_type_link>& operator=(const List& l0)
    {
        std::cout << "copy assignment\n";
        head.reset();
        auto laux = l0;
        (*this) = std::move(laux);
        return *this;
    }
  
    // destructor
    ~List()
    {
        std::cout << "List destructor\n"; 
        head.reset();
    }
  
  //print
  std::string print() 
  {
      std::string os;

      node<value_type_link>* n1;
      
      n1 = head.get();
      
      for (int i=0; i<size; i++)
      {
          os += std::to_string(n1->value) + " ";
          n1 = (n1->next).get();
      }
      
      return os;
  }
  

 //private:
     
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
            next.reset();
            (*this) = std::move(tmp);
            
            return *this;
        }
        
        // destructor
        ~node()
        {
            next.reset();
        }
    };
    
    //node constructor
    List(node<value_type_link>& n0)
    : head{new node<value_type_link>{n0}}
    , size{1}
    {std::cout <<  "node ctr" << "\n";}
    
    //begin function
    node<value_type_link>* begin() { return head.get(); }
    
    //end function
    node<value_type_link>* end() 
    { 
        auto n0 = head.get();
        for(int i=1; i<size; i++)
            n0 = (n0->next).get();
        return n0;
    }
    
    // append the newly created node at the end of the list
    void push_back(const value_type_link& v)
    {
        std::cout << "Push back" << "\n";
        if(size == 0)
        {
            head.reset(new node<value_type_link>(v));
        }
        else{
            node<value_type_link>* n_new = new node<value_type_link>;
            node<value_type_link>* n_old = end();
            n_new->value = v;
            n_old->next.reset(n_new);
        }
        size++;
    }
    
    // append the newly created node at the end of the list
    void push_front(const value_type_link& v)
    {
        
        std::cout << "Push front" << "\n";
        if(size == 0)
        {
            head.reset(new node<value_type_link>(v));
        }
        else{
            node<value_type_link>* n_new = new node<value_type_link>;
            n_new->value = v;
            n_new->next = std::move(head);
            
            head.reset(n_new);
        }
        size++;
    }
    
  std::unique_ptr<node<value_type_link>> head;
  std::size_t size;
};

template <typename T>
void List<T>::reset()
{
    List<T> l0{};
    (*this) = l0;
    return;
}

int main(void)
{
    std::cout << "#List<int> l1{1};\n";
    List<int> l1{1};
    std::cout << "\n";
    
    std::cout << "#List<int> l2{};\n";
    List<int> l2{};
    std::cout << "\n";
    
    //List<int>::node<int> n1{1};
    //List<int> l3{n1};
    //std::cout << (*l3.head.get()).value << "\n"; 
    
    std::cout << "#List<int> l4; + 3·push_back\n";
    List<int> l4;
    l4.push_back(1);
    l4.push_back(2);
    l4.push_back(3);
    std::cout << "\n";
    
    std::cout << "#List<int>* l5 = new List<int>; + 3·push_back + print l4;\n";
    List<int>* l5 = new List<int>;
    l5->push_back(5);
    l5->push_back(6);
    l5->push_back(7);
    std::cout << l4.print() << "\n";
    std::cout << "\n";
    
    if(1)
    {
        std::cout << "#SCOPED: List<int> l6 = *l5; + print l5 + delete l5 + print l6\n";
        List<int> l6 = *l5;
        std::cout << l5->print() << "\n";
        delete l5;
        std::cout << l6.print() << "\n";
        std::cout << "#END SCOPE\n";
    }
    std::cout << "\n";
                      
    std::cout << "List<int> l7 = l4;\n";
    List<int> l7 = l4;
    std::cout << "l7: " << l7.print() << "\n";
    std::cout << "l4: " << l7.print() << "\n";
    std::cout << "\n";
    
    std::cout << "List l8{8}; List l9; l9=move(l8) \n";
    std::unique_ptr<List<int>> l8 = std::make_unique<List<int>>(8);;
    std::unique_ptr<List<int>> l9;
    l9 = std::move(l8);
    //std::cout << "l8: " << l8->print() << "\n";
    std::cout << "l9: " << l9->print() << "\n";
    std::cout << "\n";
    
    std::cout << "List l10{10, 11, 12}; List l11; l10=l11 \n";
    List<int> l10;
    List<int> l11;
    l10.push_back(10);
    l10.push_back(11);
    l10.push_back(12);
    l11 = l10;
    std::cout << "l10: " << l10.print() << "\n";
    std::cout << "l11: " << l11.print() << "\n";
    l11.reset();
    std::cout << "l11: " << l11.print() << "\n";
    std::cout << "\n";
    
    std::cout << "List l12=l10; l12.push_front(12); \n";
    List<int> l12 = l10;
    std::cout << "l12: " << l12.print() << "\n";
    l12.push_front(12);
    std::cout << "l12: " << l12.print() << "\n";
    

                     
    std::cout << "#DESTRUCTION;\n";
    
    
    
    
    return 0;
}
