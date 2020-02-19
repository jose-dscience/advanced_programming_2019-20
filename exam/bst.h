/*
 * José Antonio Fernández Santisteban (DSSC student)
 * Nicola Miolato (DSSC student)
 *
 * Advanced Programming Exam
 *
 * In this source file we have implemented binary search tree class (bst). 
 * 
 * -Requirements: 
 *     +    g++ (8.3.0)
 *     +    compile with c++14
 * 
 * -Compilation: This file is a library, so it must be included in a program source file: #include"bst.h"
 *          
 */

#include <iostream>
#include <utility>
#include <memory>
#include <functional>
#include <string>

template <typename key_type, typename val_type, typename comp_type>
class bst
{
public:
    
    /******************/
    /* PUBLIC METHODS */
    /******************/
    
    /*·······················*/
    /* ORDINARY CONSTRUCTORS */
    /*·······················*/
    
    //Default constructor
    //  +INPUT: NONE
    //  +OUTPUT: NONE
    //  +COMMENTS: the default comparator is set as less comparator.
    bst()
    : _root{nullptr}
    , _beginning{nullptr}
    , _end{nullptr}
    , _size{0}
    , _comp{[](key_type const a, key_type const b) {return a<b;}}
    {}
    
    //Custom constructor (content), creates a bst initialized with one node wh
    //  +INPUT: std::pair p0, pair (key,value) with the data of the initial node.
    //  +OUTPUT: NONE
    //  +COMMENTS: the default comparator is set as less comparator.
    bst(const std::pair<key_type,val_type> p0)
    : _root{std::move(new node)}
    , _beginning{_root.get()}
    , _end{_root.get()}
    , _size{1}
    , _comp{[](key_type const a, key_type const b) {return a<b;}}
    {
        _root->content = p0;
        _root->head = _root.get();
    }
    
    //Custom constructor (comparer), creates a void bst setting a custom comparer.
    //  +INPUT: std::function f, custom comparer with the struct comp_type(ckey_type, ckey_type)
    //  +OUTPUT: NONE
    //  +COMMENTS: NONE
    bst(std::function<comp_type(const key_type, const key_type)> f)
    : _root{nullptr}
    , _beginning{nullptr}
    , _end{nullptr}
    , _size{0}
    , _comp{f}
    {}
    
    /*················*/
    /* MOVE SEMANTICS */
    /*················*/
    
    //Move constructor
    //  +INPUT: bst&& b0, r-value bst to be set on the current tree
    //  +OUTPUT: NONE
    //  +COMMENTS: NONE
    bst(bst<key_type,val_type,comp_type>&& b0)
    : _root{std::move(b0._root)}
    , _beginning{std::move(b0._beginning)}
    , _end{std::move(b0._end)}
    , _comp{std::move(b0._comp)}
    , _size{std::move(b0._size)}
    {}
    
    //Move assignment
    //  +INPUT: bst&& b0, r-value bst to be set on the current tree
    //  +OUTPUT: bst, moved tree
    //  +COMMENTS: All content of the current tree is removed
    bst& operator=(bst<key_type,val_type,comp_type>&& b0)
    {
        _root.reset(); //free memory
        _root = std::move(b0._root);
        _beginning = std::move(b0._beginning);
        _end = std::move(b0._end);
        _comp = std::move(b0._comp);
        _size = std::move(b0._size);
        return *this;
    }
    
    /*················*/
    /* COPY SEMANTICS */
    /*················*/
    
    //Copy constructor
    //  +INPUT: bst b0, tree to be copied
    //  +OUTPUT: NONE
    //  +COMMENTS: A deep copy is performed
    bst(const bst& b0)
    {
        clear();
        
        auto current = (b0._root).get();
        auto temp = current;
        auto last = current;
        
        while(current != nullptr)
        {
            insert(std::pair<key_type,val_type>(current->key(),current->val()));
            
            temp = current;
            
            //if I can go left, and I don't come from right or left, go left
            if((current->left != nullptr) && ((last != current->left.get()) && (last != current->right.get()))) 
                current = current->left.get();
            
            //if I can go right, and I don't come from right , go left
            else if((current->right != nullptr) && (last != current->right.get()))
                current = current->right.get();
            //else I go up
            else
                current = current->previous;
            
            last = temp;
        }
    }
    
    //Copy assignment
    //  +INPUT: bst b0, tree to be copied
    //  +OUTPUT: bst, copied tree
    //  +COMMENTS: A deep copy is performed
    bst& operator=(const bst& b0)
    {
        clear();
        auto baux = b0;
        (*this) = std::move(baux);
        
        return *this;
    }
    
    /*·················*/
    /* ITERATOR HEADER */
    /*·················*/
    
    template <typename O>
    class __iterator;
    using iterator = __iterator<std::pair<key_type, val_type>>;
    using const_iterator = __iterator<const std::pair<key_type, val_type>>;
    
    /*·········*/
    /* METHODS */
    /*·········*/
    
    //begin, functions which return an iterator (or const_iterator) pointing to the lowest node
    //  +INPUT: NONE
    //  +OUTPUT: iterator (const_iterator), iterator pointing to the beginning node
    //  +COMMENTS: NONE
    iterator begin(){return iterator{_beginning, _comp};}
    const_iterator begin() const {return iterator{_beginning, _comp};}
    const_iterator cbegin() const {return const_iterator{_beginning, _comp};}
    
    //end, functions which return an iterator (or const_iterator) pointing to the last past one node (null)
    //  +INPUT: NONE
    //  +OUTPUT: iterator (const_iterator), iterator pointing to nullptr
    //  +COMMENTS: NONE
    iterator end(){return iterator{nullptr, _comp};}
    const_iterator end() const {return iterator{nullptr, _comp};}
    const_iterator cend() const {return const_iterator{nullptr, _comp};}
    
    //find, functions which, given a key, search the node with the provided key
    //  +INPUT: key_type x, key to be searched
    //  +OUTPUT: iterator (const_iterator), iterator pointing to the found node (or end() if it does not exist)
    //  +COMMENTS: function implemented outside the class
    iterator find(const key_type& x);
    const_iterator find(const key_type& x) const;
    
    //insert, functions which, given a std::pair(key,value) insert it in a new node which is appended
    //  +INPUT: std::pair(key,value) content, content of the node to be appended
    //  +OUTPUT: pair(iterator,bool), the iterator points to the inserted node if did not exist, otherwise
    //           it point to the existing node, and it is not created (nor updated).
    //  +COMMENTS: function implemented outside the class
    std::pair<iterator, bool> insert(const std::pair<key_type, val_type>& mycontent);
    std::pair<iterator, bool> insert(std::pair<key_type, val_type>&& mycontent);
    
    //erase, removes (if exist) the node given its key.
    //  +INPUT: key_type x, the key whose node will be deleted
    //  +OUTPUT: NONE
    //  +COMMENTS: function implemented outside the class
    void erase(const key_type& x);
    
    //clear, removes all the content of the tree, setting a void tree.
    //  +INPUT: NONE
    //  +OUTPUT: NONE
    //  +COMMENTS: NONE
    void clear()
    {
        _beginning = nullptr;
        _end = nullptr;
        _size = 0;
        _root.reset();
    }
    
    //balance, balances the tree.
    //  +INPUT: NONE
    //  +OUTPUT: NONE
    //  +COMMENTS: 
    //      -In is only a naive implementation
    //      -function implemented outside the class
    void balance();
    
    //emplace, inserts a new node given its key and value.
    //  +INPUT: 
    //      -key_type&& key, r-value to be inserted as key
    //      -val_type&& value, t-value to be inserted as value
    //  +OUTPUT: iterator (const_iterator), iterator pointing to the found node (or end() if it does not exist)
    //  +COMMENTS: function implemented outside the class
    std::pair<iterator,bool> emplace(key_type&& key, val_type&& value);
    
    //debugging function
    //strong_print, function which prints in stdin each node of the tree with its connections.
    //  +INPUT: NONE
    //  +OUTPUT: NONE
    //  +COMMENTS: 
    //      -This function has been developed with debugging purposes, use it with attention.
    //      -The format of the output for each node is: 
    //       < left_key | current_key | right_key > [ father_key ] { root_key }
    void strong_print()
    {
        auto it = begin();
        node* n0;
        
        for(size_t i=0; i<_size; i++)
        {
            n0 = weak_find(it->first); 
            std::string s0{};
            
            if(n0->key() == it->first)
            {
                if(n0->left != nullptr)
                {
                    s0 += " <" + std::to_string((n0->left)->key());
                }
                    
                else
                    s0 += " <·";
                
                s0 += "|"; 
                s0 += std::to_string(n0->key());
                s0 += "|";
                
                if(n0->right != nullptr)
                    s0 += std::to_string((n0->right)->key()) + ">";
                else
                    s0 += "·>";
                
            }
            else
                s0 += " <·|·|·>";
            
            if(n0->previous != nullptr)
            {
                s0 += "[" + std::to_string((n0->previous)->key()) + "]";
            }
            else
                s0 += "[·]";
            
            if(n0->head != nullptr)
            {
                s0 += "{" + std::to_string((n0->head)->key()) + "}";
            }
            else
                s0 += "{·}";
            
            std::cout << s0 << std::endl;
            if(i != _size-1) ++it;
        }
        std::cout << "\n";
        
        return;
    }
    
    /*···········*/
    /* OPERATORS */
    /*···········*/
    
    //subscripting operator, it let to access to the content of a given node by providing its key
    //  +INPUT: key_type x, the key whose node will be operated
    //  +OUTPUT: val_type, value of the requested node. If the node does not exist it is created.
    //  +COMMENTS: function implemented outside the class
    val_type& operator[](const key_type& x);
    val_type& operator[](key_type&& x);
    
    /*··················*/
    /* FRIEND FUNCTIONS */
    /*··················*/
    
    //subscripting operator, provide a way to print the node 
    //  +INPUT: 
    //      -std::ostream
    //      -bst x, tree to be printed
    //  +OUTPUT: val_type, value of the requested node. If the node does not exist it is created.
    //  +COMMENTS: 
    //      -It is not a method of bst class, but an operator oveloading
    //      -the tree is printed in the format:
    //       {(key:val),(key:val),(key:val),...,(key:val)}
    //      -key_type and val_type must be compatible with << operator, otherwise it will give error.
    friend std::ostream& operator<<(std::ostream& os, bst& x)
    {
        auto it = x.begin();
        
        os << "{";
        
        if(x._size == 0)
            os << "}";
        else
        {
            for(size_t i=0; i<x._size-1; ++i)
            {
                os << "(" << it->first << ":" << it->second << "),";
                ++it;
            }
            os << "(" << it->first << ":" << it->second << "),";
            os << "\b" << "}";
        }
        
        return os;
    }

/************************************************************************************************************************/

private:
    
    /*******************/
    /* PRIVATE MEMBERS */
    /*******************/
    
    /*·············*/
    /* NODE HEADER */
    /*·············*/
    
    struct node;
    
    /*···················································································································*/
    /* MEMBERS */
    /*·········*/
    /**/
    /**/  std::unique_ptr<node> _root;                                      //unique pointer which manages the root node
    /**/  node* _beginning;                                                 //node pointer to lowest key node
    /**/  node* _end;                                                       //node pointer to greatest key node
    /**/  std::size_t _size;                                                //number of nodes of the tree
    /**/  std::function<comp_type(const key_type, const key_type)> _comp;   //function which compares two keys
    /*···················································································································*/
    
    /*·····················*/
    /* PRIVATE NODE STRUCT */
    /*·····················*/
    
    struct node
    {
        std::pair<key_type, val_type> content;  //content of the node
        std::unique_ptr<node> right;            //unique pointer which manages right node
        std::unique_ptr<node> left;             //unique pointer which manages left node
        node* previous;                         //pointer to the father node
        node* head;                             //pointer to the root node of the tree
        
        //custom ctor(content)
        explicit node(const std::pair<key_type, val_type> val) 
        : content{val}
        , right{nullptr}
        , left{nullptr}
        , previous{nullptr}
        , head{nullptr}
        {}
        
        //custom ctor(prev., pather node)
        explicit node(const std::pair<key_type, val_type> val, const node* n0)
        : content{val}
        , right{nullptr}
        , left{nullptr}
        , previous{n0}
        , head{nullptr}
        {}
        
        //custom ctor(prev., pather node, root node)
        explicit node(const std::pair<key_type, val_type> val, const node* n0, node* nr)
        : content{val}
        , right{nullptr}
        , left{nullptr}
        , previous{n0}
        , head{nr}
        {}
        
        //default ctor
        node()
        : content{std::pair<key_type, val_type>{}}
        , right{nullptr}
        , left{nullptr}
        , previous{nullptr}
        , head{nullptr}
        {}
        
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
        
        // get key
        key_type key(void) const {return content.first;}
        
        // get value
        val_type val(void) const {return content.second;}
        
        // append to my node
        node* append(const std::pair<key_type, val_type> cont, std::function<comp_type(const key_type, const key_type)> f_comp)
        {
            if(f_comp(cont.first,key()))
            {
                left.reset(std::move(new node(cont)));
                left->previous = &(*this);
                left->head = head;
                return left.get();
            }
            else
            {
                right.reset(std::move(new node(cont)));
                right->previous = &(*this);
                right->head = head;
                return right.get();
            }
        }
    };
    
    
    
    /*******************/
    /* PRIVATE METHODS */
    /*******************/
    
    //weak_find, function which, given a key, search the node that contains the key
    //  +INPUT: key_type x, the key whose node will be searched
    //  +OUTPUT: node*, pointer to the found node. If the node is not in the tree, it turns another node to which the
    //           searched node should be linked.
    //  +COMMENTS: 
    //      -this function is the "core" of find and insert functions
    node* weak_find(const key_type key) const
    {
        node* current = _root.get();
        
        if(_size == 0) return current;  //if tree is void, return nullptr
        
        do{
            if(_comp(key,current->key()))      //if key is lower, go to the left if is possible. otherwise stop
            {
                if(current->left != nullptr)
                    current = current->left.get();
                else
                    break;
            }
            else if(_comp(current->key(),key))  //if key is greater, go to the right if is possible. otherwise stop
            {
                if(current->right != nullptr)
                    current = current->right.get();
                else
                    break;
            }
            else    break;                              //else it must be equal, so found => stop
        }while(true);
        
        return current;
    }
};

/***********************************************************************************************************************/
/***********************************************************************************************************************/

/*********************/
/* BST CLASS MEMBERS */
/*********************/

//iterator class (forward iterator)
template <typename key_type, typename val_type, typename comp_type>
template <typename O>
class bst<key_type,val_type,comp_type>::__iterator 
{
    using node = typename bst<key_type,val_type,comp_type>::node;
    std::function<comp_type(const key_type, const key_type)> f_comp;
    node* current;
    key_type threshold;

public:
    explicit __iterator(node* n0, std::function<comp_type(const key_type, const key_type)> comp) noexcept 
    : f_comp {comp} 
    , current{n0}
    {}

    using value_type = O;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using reference = value_type&;
    using pointer = value_type*;

    reference operator*() const noexcept { return current->content; }
    pointer operator->() const noexcept { return &(*(*this)); }
    
    
    __iterator& operator++() noexcept 
    {  
        if(current->right != nullptr)
        {
            //search min right child
            current = current->right.get();
            //std::cout << "'->\n";             //<- eliminate comments for print
            while(current->left != nullptr)     //   iterator movements along the
            {                                   //   tree
                //std::cout << "<-'\n";
                current = current->left.get();
            }
        }
        else
        {
            //search min pather greater than current node
            auto original_node = current;

            while(!f_comp(original_node->key(),current->key())){
                //std::cout << "/|\\\n";
                current = current->previous;
            }
        }
        
        return *this;
    }

    __iterator operator++(int) noexcept 
    {
        __iterator tmp{current};
        ++(*this);
        return tmp;
    }

    friend bool operator==(const __iterator& a, const __iterator& b) 
    {
        return a.current == b.current;
    }
    friend bool operator!=(const __iterator& a, const __iterator& b) 
    {
        return !(a == b);
    }
    
    friend void bst<key_type,val_type,comp_type>::erase(const key_type& x);
};


//find, functions which, given a key, search the node with the provided key
//  +COMMENTS: details in the asociated header within the class

template <typename key_type, typename val_type, typename comp_type>
typename bst<key_type,val_type,comp_type>::iterator bst<key_type,val_type,comp_type>::find(const key_type& x)
{
    iterator it(weak_find(x),_comp);
    
    if((*it).first == x) return it;
    else return end();
}

template <typename key_type, typename val_type, typename comp_type>
typename bst<key_type,val_type,comp_type>::const_iterator bst<key_type,val_type,comp_type>::find(const key_type& x) const
{
    const_iterator it{weak_find(x),_comp};
    
    if((*it).first == x) return it;
    else return cend();
}


//insert, functions which, given a std::pair(key,value) insert it in a new node which is appended
//  +COMMENTS: details in the asociated header within the class

template <typename key_type, typename val_type, typename comp_type>
std::pair<typename bst<key_type,val_type,comp_type>::iterator, bool> bst<key_type,val_type,comp_type>::insert(const std::pair<key_type, val_type>& mycontent)
{
    if(_size == 0)  //if tree is void, call custom constructor
    {
        (*this) = std::move(bst<key_type,val_type,comp_type>(mycontent));
        return std::pair<iterator, bool>(begin(),true);
    }
    
    auto n0 = weak_find(mycontent.first);
    
    if(n0->key() == mycontent.first)                      //if mycontent's key is found, don't insert
        return std::pair<iterator, bool>(iterator(n0,_comp),false);
    else
    {
        auto new_node = n0->append(mycontent,_comp);
        if(_comp(mycontent.first,begin()->first)) //check if it changes the beginning/ending pointer
            _beginning = new_node;
        else if(_comp(_end->key(),mycontent.first))
            _end = new_node;
        _size++;
        
        return std::pair<iterator, bool>(iterator(new_node,_comp),true);
    }
}

template <typename key_type, typename val_type, typename comp_type>
std::pair<typename bst<key_type,val_type,comp_type>::iterator, bool> bst<key_type,val_type,comp_type>::insert(std::pair<key_type, val_type>&& mycontent)
{
    std::pair<key_type, val_type> p0(mycontent.first,mycontent.second);
    return insert(p0);
}


//subscripting operator, it let to access to the content of a given node by providing its key
//  +COMMENTS: details in the asociated header within the class

template <typename key_type, typename val_type, typename comp_type>
val_type& bst<key_type,val_type,comp_type>::operator[](const key_type& x)
{
    auto n0 = weak_find(x);
    
    if(n0->key() == x)
        return n0->content.second;
    else
    {
        val_type a{};
        auto new_node = insert(std::pair<key_type, val_type>(x,a)).first;
        return new_node->second;
    }
}

template <typename key_type, typename val_type, typename comp_type>
val_type& bst<key_type,val_type,comp_type>::operator[](key_type&& x)
{
    key_type key = x;
    return operator[](key);
}


//erase, removes (if exist) the node given its key.
//  +COMMENTS: details in the asociated header within the class
template <typename key_type, typename val_type, typename comp_type>
void bst<key_type,val_type,comp_type>::erase(const key_type& x)
{
    auto n0 = weak_find(x);
    bool root_changed = false;
    
    if(n0->key() == x)
    {
        auto n0l = std::move(n0->left);  //remove left child custody
        auto n0r = std::move(n0->right); //remove left child custody
        
        //
        //conditions to set the children
        //
        if(_size <= 1) //If my tree has 1 or 0 elements, I set it to the null tree.
        {
            bst b0{};
            clear();
            (*this) = std::move(b0);
            _size=1;
        }
        else if((n0->key() == _root->key()) && (n0r != nullptr))   //if I'm the root, my right (if exist) becomes the new root
        {
            _root.reset();
            _root = std::move(n0r);
            _root->previous = nullptr;
            root_changed = true;
        }
        else if((n0->key() == _root->key()) && (n0l != nullptr))   //if I'm the root, my left (if exist) becomes the new root
        {
            _root.reset();
            _root = std::move(n0l);
            _root->previous = nullptr;
            root_changed = true;
        }
        else if(((n0->previous)->left)->key() == n0->key())  //if I'm left, my father erase his left
        {
            (n0->previous)->left.reset();
        }
        else
        {
            (n0->previous)->right.reset();  //if I'm right, my father erase his right
        }
        
        if(n0l != nullptr)      //search home for left child if exists
        {
            auto tmp = weak_find(n0l->key());
            n0l->previous = &(*tmp);
            if(_comp(n0l->key(),tmp->key()))
                tmp->left = std::move(n0l);
            else
                tmp->right = std::move(n0l);
        }
        
        if(n0r != nullptr)      //search home for right child if exists
        {
            auto tmp = weak_find(n0r->key());
            n0r->previous = &(*tmp);
            if(_comp(n0r->key(),tmp->key()))
                tmp->left = std::move(n0r);
            else
                tmp->right = std::move(n0r);
        }
        
        
        if(_size <= 1)
        {
            _beginning = nullptr;
            _end = nullptr;
        }
        else if(_beginning == nullptr)   //if I was beginning, search new beginning node
            _beginning = weak_find(x);
        else if(_end == nullptr)     //if I was end, search new end node
            _end = weak_find(x);
        
        
        _size--;
        
        
        if(root_changed)
        {
            auto it = begin();
            for(size_t i = 0; i < _size-1; ++i)
            {
                (it.current)->head = _root.get();
                ++it;
            }
            (it.current)->head = _root.get();
        }
    }
    return;
}


//balance, balances the tree.
//  +COMMENTS: details in the asociated header within the class
template <typename key_type, typename val_type, typename comp_type>
void bst<key_type,val_type,comp_type>::balance()
{
    auto it = begin();
    bst b0{};
    
    for(size_t i=0; i<_size/2-1; ++i) //copy all values into the vector (sorted)
        ++it;
    
    b0.insert(*it);
    erase(it->first);
    
    while(_size > 0)
    {
        b0.insert(std::pair<key_type,val_type>(_root->key(),_root->val()));
        erase(_root->key());
    }
    
    clear();
    *this = std::move(b0);
}


//emplace, inserts a new node given its key and value.
//  +COMMENTS: details in the asociated header within the class
template <typename key_type, typename val_type, typename comp_type>
std::pair<typename bst<key_type,val_type,comp_type>::iterator,bool> bst<key_type,val_type,comp_type>::emplace(key_type&& key, val_type&& value)
{
    std::pair<key_type, val_type> mycontent(key, value);
    return insert(mycontent);
}
