/*
 * @Author: Lr-2002 
 * @Date: 2022-01-10 20:24:18 
 * @Last Modified by: Lr-2002
 * @Last Modified time: 2022-01-11 11:34:57
 */

#include <type_traits>
#include <iostream>
#include <string>

using namespace std;

template <typename T , size_t N>
class MyClass
{
public:

    template<typename ...Args>
    void emplace_back(Args&&... args)
    {
        if (m_size >= N)
        {
            throw bad_alloc{};
        }

        // new(placement_parameters) (type) initializer
        // forward change variables to the rvalue
        // so it change args to rvalue
        
        //firstly the args was used like this
        // MyClass<int,10> a;
        // a.emplace_back(10,1);
        // this was error because the int has no member of int()

        new(&data[m_size]) T (forward<Args>(args)...);
        ++m_size;
        
        // cout<<m_size<< endl;
    }

    const T& operator[](std::size_t index) const
    {
        return *reinterpret_cast<const T* >(&data[index]);
    }

    ~MyClass()
    {
        for(size_t i = 0 ; i < m_size ; ++i)
        {
            // reinterpret_cast<newtype> (expression)
            reinterpret_cast<T*>(&data[i])->~T();
        }
    }

private:
    typename aligned_storage<sizeof(T), alignof(T)>::type data[N];
    
    // stand for different layers of the storage 
    size_t m_size = 0;
};


int main(int argc, char* argv[])
{
    MyClass<string, 10> v1;
    v1.emplace_back(5, 'c');
    v1.emplace_back(10, 'c');
    cout<<v1[0] <<" \n" << v1[1] ;
    return 0;
}