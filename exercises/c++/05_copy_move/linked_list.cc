#include<iostream>
#include<memory>
#include<algorithm>
#include<string>

enum class Insertion_method { push_back, push_front };

template <class value_type_link>
class List {
 public:
     
    /********************/
    /* PUBLIC FUNCTIONS */
    /********************/
    
    void insert(const value_type_link& v, const Insertion_method m);
    
    //Function which returns the current size of the list
    //  +INPUT: NONE
    //  +OUTPUT: const size_t, number of elements of the list
    //  +COMMENTS: NONE
    std::size_t mysize() const  
    {
        return size;
    }

    //Function which reset the list
    //  +INPUT: NONE
    //  +OUTPUT: NONE
    //  +COMMENTS:  +If there are nodes within the list, it deletes all the nodes (and its memory if necessary)
    //             and set void the list.
    //              +Implemented outside the class
    void reset();
    
    //Function which print the list in an string
    //  +INPUT: NONE
    //  +OUTPUT: string, value of the list
    //  +COMMENTS: The value type of the template must support a string representation.
    std::string print() 
    {
        std::string os;

        node<value_type_link>* n1;
        
        if(size>0)
        {
            n1 = head.get();
            for (int i=0; i<size; i++)
            {
                os += std::to_string(n1->value) + " ";
                n1 = (n1->next).get();
            }
        }
        else
            os+="null";
        
        return os;
    }

    
    
    /******************************************/
    /* constructor(s) and destructor for List */
    /******************************************/
    
    //Custom constructor: constructs a list with one single node whose value is given.
    //  +INPUT: const value_type_link val, value of the head node.
    //  +OUTPUT: NONE
    //  +COMMENTS:  head->next by default is nullptr.
     explicit List(const value_type_link val) 
    : head{std::move(new node<value_type_link>)}
    , size{1}
    {
        head->value=val;
        //std::cout <<  "custom ctr" << "\n";
    }
    
    //Default constructor: constructs a void list.
    //  +INPUT: NONE
    //  +OUTPUT: NONE
    //  +COMMENTS:  head by default is nullptr.
    List()
    : head{nullptr}
    , size{0}
    {/*std::cout <<  "default ctr" << "\n";*/}
    
    //Copy constructor (copy semantics): constructs a list by copying another list
    //  +INPUT: const List& l0, list whose content will be copied.
    //  +OUTPUT: NONE
    //  +COMMENTS:  The resultant list is an new list independent from
    //              the original one. New nodes are linked inside the 
    //              new list, not with nodes of the old list
    List(const List& l0)
    : size{l0.size}
    , head{nullptr}
    {
        //std::cout << "copy ctr" << "\n";
        
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
    
    //Move constructor (move semantics): moves an existing list to a new created list
    //  +INPUT: const List& l0, list whose content will be copied.
    //  +OUTPUT: NONE
    //  +COMMENTS:  l0 list is destructed when this constructor is invoked.
    List(List<value_type_link>&& l0)
    : size{std::move(l0.size)}
    , head{std::move(l0.head)}
    {/*std::cout << "Move ctor\n";*/}
    
    //Destructor: Destructs the current list
    //  +INPUT: NONE
    //  +OUTPUT: NONE
    //  +COMMENTS: NONE
    ~List()
    {
        //std::cout << "List destructor\n"; 
        head.reset();
    }
    
    
    
    /*******************************/
    /* PUBLIC OVERLOADED OPERATORS */
    /*******************************/
    
    //Move assignment (move semantics): Moves one list to the current pointer
    //  +INPUT: List<value_type_link>&& l0, List to be moved.
    //  +OUTPUT: Moved list.
    //  +COMMENTS:  
    //      -New_list = std::move(l0)
    //      -It is not only copy the values of l0, it moves it!!!
    //      -l0 remains void.
    //      -If it was any content on the current pointer, it is removed.
    List<value_type_link>& operator=(List<value_type_link>&& l0)
    {
        //std::cout << "move assignment\n";
        head.reset();
        size = std::move(l0.size);
        head = std::move(l0.head);
        return *this;
    }
    
    //Copy assignment (copy semantics): Copy the content of a given list in the current pointer
    //  +INPUT: const List& l0, List to be copied.
    //  +OUTPUT: Copied list.
    //  +COMMENTS:  
    //      -New_list = l0
    //      -It copy the values in a similar way as copy constructor
    //      -If it was any content on the current pointer, it is removed.
    List<value_type_link>& operator=(const List& l0)
    {
        //std::cout << "copy assignment\n";
        head.reset();
        auto laux = l0;
        (*this) = std::move(laux);
        return *this;
    }
  

 private:
     
    /**********************/
    /* PRIVATE NODE CLASS */
    /**********************/ 
    
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
    
    
    
    /*********************/
    /* PRIVATE FUNCTIONS */
    /*********************/
    
    //Node constructor: Creates and initializes a list for a given node
    //  +INPUT: node<value_type_link>& n0, node to set as head node.
    //  +OUTPUT: NONE
    //  +COMMENTS:  This constructor has been created for debugging purposes,
    //              but it could eventually have other uses.
    List(node<value_type_link>& n0)
    : head{new node<value_type_link>{n0}}
    , size{1}
    {/*std::cout <<  "node ctr" << "\n";*/}
    
    //Function which gives a pointer pointing to head node
    //  +INPUT: NONE
    //  +OUTPUT: node<value_type_link>*, pointer that points to head node.
    //  +COMMENTS: The returned pointer is not std::unique_ptr.
    node<value_type_link>* begin() { return head.get(); }
    
    //Function which gives a pointer pointing to the last node
    //  +INPUT: NONE
    //  +OUTPUT: node<value_type_link>*, pointer that points to the last node.
    //  +COMMENTS: The returned pointer is not std::unique_ptr.
    node<value_type_link>* end() 
    { 
        auto n0 = head.get();
        for(int i=1; i<size; i++)
            n0 = (n0->next).get();
        return n0;
    }
    
    //Function which append a newly created node at the end of the list
    //  +INPUT: const value_type_link& v, content of the new node
    //  +OUTPUT: NONE
    //  +COMMENTS: NONE
    void push_back(const value_type_link& v)
    {
        //std::cout << "Push back" << "\n";
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
    
    //Function which append a newly created node at the beginning of the list
    //  +INPUT: const value_type_link& v, content of the new node
    //  +OUTPUT: NONE
    //  +COMMENTS: NONE
    void push_front(const value_type_link& v)
    {
        
        //std::cout << "Push front" << "\n";
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
    
    
    
    /*******************/
    /* PRIVATE MEMBERS */
    /*******************/
    
    std::unique_ptr<node<value_type_link>> head;
    std::size_t size;
};

//reset
template <typename T>
void List<T>::reset()
{
    List<T> l0{};
    (*this) = l0;
    return;
}

//operator <<
template <class T>
std::ostream& operator<<(std::ostream& os, const List<T>& l)
{
    std::string oss;
    List<int> l0 = l;
    os << l0.print();
    return os;
}

//insert
template <class T>
void List<T>::insert(const T& v, const Insertion_method m)
{
    switch (m)
    {
        case Insertion_method::push_front:
            push_front(v);
            break;
        default:
            push_back(v);
    }
}

int main(void)
{
    Insertion_method end{Insertion_method::push_back};
    Insertion_method start{Insertion_method::push_front};
    
    std::cout << "List l0{1}; l0.insert(1, end); l0.insert(2, start); l0.reset();\n";
    List<int> l0{0};
    l0.insert(1, end);
    l0.insert(2, start);
    std::cout << l0 << "\n";
    l0.reset();
    std::cout << l0 << "\n";
    std::cout << std::endl;
    
    std::cout << "List l1; l1.insert(1, start); l1.insert(2, start); l1.insert(3, end);\n";
    List<int> l1;
    std::cout << l1 << "\n";
    l1.insert(1, start);
    l1.insert(2, start);
    l1.insert(3, end);
    std::cout << l1 << "\n";
    std::cout << std::endl;
    
    std::cout << "List l1; List l2 = std::move(l1);\n";
    List<int> l2 = std::move(l1);
    std::cout << "l2: " << l2 << "\n";
    std::cout << std::endl;
    
}
