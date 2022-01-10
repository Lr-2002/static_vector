/*
 * @Author: Lr-2002 
 * @Date: 2022-01-06 20:24:11 
 * @Last Modified by: Lr-2002
 * @Last Modified time: 2022-01-09 22:56:12
 */
#include <vector>
#include <memory>
#include <iostream>
#include <array>


template <typename Ty, std::size_t L>
class static_vector
{
public:
    using value_type             = Ty;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    // define iterator
    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = pointer;
    using const_reverse_iterator = const_pointer;

    constexpr static_vector() noexcept;                             // (1)
    constexpr static_vector(const static_vector& other);            // (2)
    constexpr static_vector(static_vector&&) noexcept;              // (3)
    constexpr static_vector(std::initializer_list<value_type> list);// (4)
    constexpr explicit static_vector(std::size_t n);                // (5)   initialized with L
    constexpr static_vector(std::size_t, const_reference v);        // (6)
    template<std::size_t length>
    constexpr static_vector(const value_type(&)[length]);                // (7) 
    template<std::size_t length>
    constexpr static_vector(const value_type(*)[length]);                // (7) 
    template<typename Iter>
    constexpr static_vector(Iter beg, Iter end);                    // (8)
    ~static_vector() {}
    constexpr static_vector& operator=(const static_vector& other); 
    constexpr static_vector& operator=(static_vector&& other) noexcept; 
    // constexpr static_vector& operator=(
    //     std::initializer_list<value_type>
    // );
    
public: // iterator
    constexpr reference at(size_type n)
    {
        
        if(n < 0 || n > size())
        {
            throw std::out_of_range("function [at] call invalid size");
        }


        // pointer tmp = _begin; 
        // std::cout<<"at" << std::endl;
        return *(_begin + n);
    }

    // constexpr const_reference at(size_type n) const
    // { // todo no idea
    //     const_reference tmp = _begin;
    //     std::cout<<"const at" << std::endl;
    //     return *(tmp+n);
    // }
    constexpr reference operator[](size_type n) 
    {
        return at(n);
    }

    // constexpr const_reference operator[](size_type n) const
    // todo no idea

    constexpr reference front()
    {
        if (size() == 0)
        {
            std::cout<<"front called undefined behavior" << std::endl;
            return NULL;
        }
        return *_begin;
    }

    constexpr reference back()
    {
        if(size() == 0)
        {
            std::cout<<"back called undefined behavior" <<std::endl;
            return NULL; 
        }
        return *_end; 
    }
    constexpr pointer data() 
    {
        return _begin;
    }

    constexpr pointer end()
    {
        return _end;
    }
    constexpr pointer begin()
    {
        return _begin;
    }


    constexpr size_type size() const noexcept
    {
        // size will add when append 
        return _size;
    }
    constexpr bool full() const noexcept
    {
        if(size() == L)
        {
            return true;
        }
        return false;
    }
    constexpr bool empty() const noexcept
    {
        if(size() == 0)
        return true;
        return false;
    }

    constexpr size_type capacity() const noexcept
    {
        return _capacity;
    }
    
    void copy(const static_vector<Ty, L> &other) 
    {
        pointer iter = begin();
        const_iterator const_iter = other.begin();
        while(const_iter != other.end())
        {
            *iter = *const_iter;
        }
    }

    void init()
    {
        init(_capacity);
    }

    void init(std::size_t n)
    {
        if( n > _capacity )
        {
            std::cout<< "Undefined Behavor of calling bigger space than L" <<std::endl;
            return; 
        }
        // Ty _element[n];
        _size = n;
        _begin = _element;
        _end = _begin + n;
    }

    void init(std::size_t n, const_reference var)
    {
        if( n > _capacity)
        {
            std::cout<< "Undefined Behavor of calling bigger space than capacity" <<std::endl;
            return; 
        }
        init(n);
        pointer _initial_iter = _begin;
        while (_initial_iter < _end)
        {
            /* code */
            *_initial_iter = var;
        }
        
    }

private: 
    // std::allocator<Ty> _alloc;
    pointer _begin = NULL;
    pointer _end   = NULL;
    value_type _element[L];
    size_type _size = L;
    size_type _capacity = L;
    // Ty * element;

};

template<typename Ty, std::size_t L>
constexpr static_vector<Ty, L>::static_vector() noexcept{
    init();
    std::cout<<"using [ default ] constructor and the default value of begin is "<<*_begin << std::endl;
}

template<typename Ty, std::size_t L>
constexpr static_vector<Ty, L>::static_vector(const static_vector<Ty, L>& other) 
{
    // todo copy the value of this function
    
    init();
    copy(other);
    std::cout<<"using [ copy ] constructor "<<std::endl;
}

template<typename Ty, std::size_t L>
constexpr static_vector<Ty, L>::static_vector(static_vector<Ty, L>&& other) noexcept
{
    // construct this one and move other to NULL
    // todo need to alloc again?
    init();
    _begin = other._begin;
    _end = other._end;
    other._begin = NULL;
    other._end = NULL;
    std::cout<<"using [ move ] constructor "<<std::endl;
}

// template<typename Ty, std::size_t L>
// static_vector<Ty, L>::~static_vector()
// {
//     // std::cout<<"calling deallocate"<< std::endl;
// }

template<typename Ty, std::size_t L>
constexpr static_vector<Ty, L>::static_vector(std::initializer_list<value_type> list)
{
    // todo copy value
    // _begin = list.begin();
    // _end = list.end();
    init(list.size());
    std::cout<<"using [ initializer_list ] constructor "<<std::endl;
}

template<typename Ty, std::size_t L>
constexpr static_vector<Ty, L>::static_vector(std::size_t n)
{
    init(n);
    std::cout<<"using [ size_t ] constructor "<<std::endl;
}

template<typename Ty, std::size_t L>
constexpr static_vector<Ty, L>::static_vector(std::size_t n, const Ty& var)
{
    init(n, var);
    auto it = _end;
    it--;
    std::cout<<"using [ size_t and var ] constructor and the random value is "<< *it <<std::endl;
}

template<typename Ty, std::size_t L>
template<std::size_t length>
constexpr static_vector<Ty, L>::static_vector(const value_type(&)[length])
{
    static_assert(length <= L , "Undefined behavior");

    init(length);
    std::cout<<"using [ reference ] constructor " <<std::endl;
    
}

template<typename Ty, std::size_t L>
template<std::size_t length>
constexpr static_vector<Ty, L>::static_vector(const Ty(*)[length])
{
    static_assert(length <= L , "Undefined behavior");
    init(length);

    std::cout<<"using [ pointer ] constructor " <<std::endl;
}

template<typename Ty, std::size_t L>
template<typename Iter>
constexpr static_vector<Ty, L>::static_vector(Iter beg, Iter end)
{
    std::size_t size = end - beg;
    if(size > L)
    {
        std::cout<<" Undefined Behavor"<<std::endl;
        return;
    }

    init(size);
    std::cout << "using [ Iter ] constructor "<<std::endl;
}

template<typename Ty, std::size_t L>
constexpr static_vector<Ty, L>& static_vector<Ty, L>::operator=(const static_vector<Ty, L>& other)
{
    // must copy
    init();
    std::cout<<"using [ operator = ] constructor 2 "<<std::endl;
    return *this;
}

template<typename Ty, std::size_t L> 
constexpr static_vector<Ty, L>& static_vector<Ty, L>::operator=(static_vector<Ty, L>&& other) noexcept
{
    init();
    std::cout<<"using [ operator = ] constructor 1 ";

    return *this;
}


static_vector<int, 5> get_vector()
{

    static_vector<int, 5> ee(5, 4);
    int * iter = ee.begin();
    while(iter != ee.end())
    {
        std::cout << *iter <<std::endl;
        iter++;
    }
    return ee;    
}


class vec
{
public:
    vec() 
    {
        std::cout<<"using constructor"<<std::endl;
    }
    
};

int main() {

    static_vector<int, 5> a(4);
    std::cout<<std::endl;
    static_vector<int, 5> b(get_vector());
    std::cout<<std::endl;

    int* iter = a.data();

    int i = 0;
    while(iter != a.end())
    {
        std::cout<<"iter: "<<*iter<<" " << b[i++] << std::endl;  
        iter ++;
    }
    int *beg = a.begin();
    *beg = 0;

    iter = a.data();
    std::cout<<"--------------------------------------"<<std::endl;
    i = 0;
    while(iter != a.end())
    {
        std::cout<<"iter: "<<*iter<<" " << b[i++] << std::endl;  
        iter ++;
    }

    std::cout<< a.size() << "   " << a.capacity() << std::endl;

    return 0;   
}
