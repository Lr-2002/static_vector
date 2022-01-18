/*
 * @Author: Lr-2002 
 * @Date: 2022-01-06 20:24:11 
 * @Last Modified by: Lr-2002
 * @Last Modified time: 2022-01-10 20:28:57
 */
#include <vector>
#include <memory>
#include <iostream>
#include <array>
#include <type_traits>
// #include <glog/logging.h>


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
     constexpr static_vector& operator=(
         std::initializer_list<value_type>
     );


    constexpr void push_back(const_reference value)
    {
        if(size() >= _capacity)
        {
            throw std::length_error("length overflow");
        }
        new(_end++) Ty(value);
        return;
    }

    constexpr void push_back(value_type&& value)
    {
        if(size() >= _capacity)
        {
            throw std::length_error("length overflow");
        }
        new(_end++) Ty(value);
        return;
    }

    constexpr void pop_back() noexcept
    {
        // TODO no destroy
        _end --;
    }


    

    template<class... Args>
    constexpr reference emplace_back(Args&&... args)
    {
        if(size() >=_capacity)
        {
            throw std::length_error("can not to emplace_back ");
        }
        
        return  *(new(_end++) Ty(std::forward<Args>(args)...)); 
    }

public: // iterator
    constexpr reference at(size_type n)
    {
        
        if(n < 0 || n >= size())
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

    constexpr pointer end() const
    {
        return _end;
    }
    constexpr pointer begin() const
    {
        return _begin;
    }

    constexpr size_type size() const noexcept
    {
        // size will add when append 
        return end() - begin();
    }
    constexpr bool full() const noexcept
    {
        if(size() == L)
        {
            return true;
        }
        return false;
        copy
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
        pointer const_iter = other.begin();
        while(const_iter != other.end())
        {
            *iter = *const_iter;
            iter++;
            const_iter++;
        }
        iter = nullptr;
        const_iter = nullptr;
    }


    void init(std::size_t n)
    {
        // call in necesary 
        // create n object
        if( n > _capacity )
        {
            std::cout <<"Make sure your size is less than the capacity" <<std::endl;
            return; 
        }

        _size = n;
        _end = _begin + n;
        pointer iter = begin();
        while ( iter != _end )
        {
            new(iter) Ty();
            iter++;
        }
        iter = nullptr;
    }

    void init(std::size_t n, const_reference var)
    {
        if( n > _capacity)
        {
            std::cout<< "Undefined Behavor of calling bigger space than capacity" <<std::endl;
            return; 
        }
        _size = n;
        _end = _begin + n; 

        pointer _initial_iter = begin();
        while (_initial_iter < _end)
        {
            std::cout << "Initializing element"<< var << std::endl;
            new(_initial_iter) Ty(var);
            _initial_iter++;
        }
        _initial_iter = nullptr;
    }


    void show()
    {
        std::cout << size() << std::endl;     
        std::cout << capacity() << std::endl;
        std::cout << empty() << std::endl;
        std::cout << full() << std::endl;
    }
private: 
    // std::allocator<Ty> _alloc;



    typename  std::aligned_storage<sizeof(Ty), alignof(Ty)>::type _element[L];
    pointer _begin = reinterpret_cast<Ty *>(&_element[0]);
    pointer _end   = _begin;
    size_type _size = 0;
    size_type _capacity = L;

};

template<typename Ty, std::size_t L>
constexpr static_vector<Ty, L>::static_vector() noexcept{
    // todo no make object
    // init(L);
    std::cout<<"using [ default ] constructor and the default value of begin is "<<std::endl;
}

template<typename Ty, std::size_t L>
constexpr static_vector<Ty, L>::static_vector(const static_vector<Ty, L>& other) 
{
    // todo copy the value of this function
    if(other.size() > L) 
    {
        throw std::length_error("[copy] error in your length");
    }
    init(other.size());
    std::copy(other.begin(), other.end(), _begin);
    std::cout<<"using [ copy ] constructor "<<std::endl;
}

template<typename Ty, std::size_t L>
constexpr static_vector<Ty, L>::static_vector(static_vector<Ty, L>&& other) noexcept
{
    // todo need to alloc again?'
    
    init(other.size());
    std::move(other.begin(), other.end(), begin());
    // TODO move just change the l-value to r-value ,why the third parameter
    // _element = other._element;

    std::cout<<"using [ move ] constructor "<<std::endl;
}

template<typename Ty, std::size_t L>
constexpr static_vector<Ty, L>::static_vector(std::initializer_list<value_type> list)
{   
    init(list.size());
    std::copy(list.begin(), list.end(), begin());
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
    std::cout<<"the size of the reference costructor is " << length << std::endl;
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
    std::copy(beg, end, _begin);
    std::cout << "using [ Iter ] constructor "<<std::endl;
}

template<typename Ty, std::size_t L>
constexpr static_vector<Ty, L>& static_vector<Ty, L>::operator=(const static_vector<Ty, L>& other)
{
    // must copy
    init(other.size());
    copy(other);
    std::cout<<"using [ operator = ] constructor 2 with l-value "<<std::endl;
    return *this;
}

template<typename Ty, std::size_t L> 
constexpr static_vector<Ty, L>& static_vector<Ty, L>::operator=(static_vector<Ty, L>&& other) noexcept
{
    init(other.size());
    std::move(other.begin(), other.end(), _begin);
    std::cout<<"using [ operator = ] constructor with r-value " << std::endl;
    return *this;
}

template<typename Ty, std::size_t L >
constexpr static_vector<Ty, L>& static_vector<Ty, L>::operator=(std::initializer_list<Ty> list)
{
    init(list.size());
    std::copy(list.begin(), list.end(), _begin);
    std::cout<<"using [ operator = ] constructor with list initializer-list" << std::endl;
    return *this;
}


class vec
{
public:
    int a = 2;
    char b = ' ';
    vec(int a, char b) : a(a), b(b) {}
    vec() {}
    ~vec() {}
    void show()
    {
        std::cout <<"This is the vector" << std::endl;
        std::cout << a<< std::endl;
        std::cout << b<< std::endl;
    }
};

static_vector<int, 5> get_vector()
{
    static_vector<int, 5> e(5);
    e.init(5, 2);
    return e;
}


int main() {
    // static_vector<int, 5> a(5);
    // a.init(5, 3);
    // static_vector<int, 5> c(get_vector());
    // int * iter = c.begin();
    // while (iter != c.end())
    // {
    //     std::cout << *iter << std::endl;
    //     iter ++ ;
    // }
    
    
    // // std::cout<< a.at(1) << std::endl;

    // static_vector<vec, 5> b(5);
    // static_vector<vec, 5> d(b);
    // // seem [copy] is also ok
    // std::cout << d[4].a << std::endl;


    // static_vector<int, 5> e(std::initializer_list<int> {1,2,3,4,5});
    // static_vector<int, 5> ee = std::initializer_list<int> {1,2,3,4,5};
    // for(auto it = ee.begin(); it != ee.end();it++)
    // {
    //     std::cout << *it << std::endl;
    // }

    // int arr[4] = {1,2,3,4};
    // static_vector<int, 5> f(arr);

    // static_vector<int, 5> g(a.begin(), a.end());
    // for(auto it = g.begin(); it != g.end();it++)
    // {
    //     std::cout << *it << std::endl;
    // }
    // // static_vector<int, 5> g([1,2,3]);z
    // static_vector<int, 5> h = g;
    // std::cout << h[0] << std::endl;



    // static_vector<vec, 3> vec_a;
    // static_vector<vec, 3> vec_b = vec_a;
    // std::cout<<vec_a[2].a << std::endl;
    // iter = nullptr;
    static_vector<vec, 3> a;
    a.show();

    a.emplace_back(3,'a');
    a.push_back(a[0]);
    a.push_back(std::move(a[1]));
    a.pop_back();
    a.show();

    a[1].show();
    return 0;   
}

/* todo
 * 
 * when init 
 * you should not 
 * give the object 
 * and then
 * you should new the object 
 * when you push back
 *
 */