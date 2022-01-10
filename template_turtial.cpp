/*
 * @Author: Lr-2002 
 * @Date: 2022-01-07 15:38:22 
 * @Last Modified by: Lr-2002
 * @Last Modified time: 2022-01-07 16:27:59
 */

#include <iostream>

template <typename T> class ClassA;

template <typename T> class ClassA
{
    T member;
};
float data[1024];
template <typename T> T get_value(int i )
{
    return static_cast<T>(data[i]);
}
int a = get_value<int>(0);


template <typename T> class TypeToId
{
public:
    static int const ID = -1;
};

// template <> class TypeToId<uint8_t>
// {
// public:
//     static int const ID = 0;
// };

// template <> class TypeToId<void *>
// {
// public:
//     static int const ID = 0x3300;
// };

template <typename T> 
class TypeToId<T*>
{
public:
    typedef T same_as_t;
    static int const ID = 0x8000000;
};


int main(int argc, char **argv)
{
    std::cout << TypeToId<TypeToId<float*>::same_as_t>::ID << std::endl;
}